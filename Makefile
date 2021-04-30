# Tools used by the Makefile.
CP          = cp -f
MKDIR       = mkdir -vp
DIFF        = diff --color=always
GREP        = grep
RSYNC       = rsync
RSYNC_OPTS  = -avhi -c --no-t
J2          = j2
J2_OPTS     = --undefined=normal --filters j2_filters.py --tests j2_tests.py --

# rsync options note:
#   -h      -> human readable
#   -i      -> itemize changes
# 	-c      -> files are copied based on changed checksum
# 	--no-t  -> turn of -t (implied by -a) to avoid updating timestamps


# Enable secondary expansion, used by the generic recipes.
.SECONDEXPANSION:

# Configuration variables, affecting the processing of templates.
OUTDIR          = output
TPLDIR          = tpl/m000
HOSTNAME        = $(shell uname -n | tr A-Z a-z)
HOSTNAME_SHORT  = $(shell uname -n | cut -d. -f1 | tr A-Z a-z)
KERNEL          = $(shell uname -s | tr A-Z a-z)

# Set base config - optional.
CONFIG_BASE     = config/base.json
ifeq ($(realpath $(CONFIG_BASE)),)
CONFIG_BASE     =
endif

# Set os config - optional.
CONFIG_OS       = config/base_$(KERNEL).json
ifeq ($(realpath $(CONFIG_OS)),)
CONFIG_OS       =
endif

# Set host config - mandatory.
CONFIG_HOST     = config/host_$(KERNEL)_$(HOSTNAME).json
ifeq ($(realpath $(CONFIG)),)
CONFIG_HOST     = config/host_$(KERNEL)_$(HOSTNAME_SHORT).json
endif
ifeq ($(realpath $(CONFIG_HOST)),)
$(error No configuration file for this host in $(CONFIG_HOST))
endif

CONFIG          = $(CONFIG_BASE) $(CONFIG_OS) $(CONFIG_HOST)

# List of non-hidden template files. To compiled with j2cli.
RCFILES_IN      = $(shell find $(TPLDIR) \( -type f -or -type l \) -not -iname '.*' -iname '*.j2')
RCFILES_OUT     = $(subst /_,/.,$(patsubst $(TPLDIR)/%.j2,$(OUTDIR)/%,$(RCFILES_IN)))

# List non-hidden files that are not a templates. To be copied without processing.
RCFILES_CPIN 	= $(shell find $(TPLDIR) \( -type f -or -type l \) -not -iname '.*' -not -iname '*.j2')
RCFILES_CPOUT   = $(subst /_,/.,$(patsubst $(TPLDIR)/%,$(OUTDIR)/%,$(RCFILES_CPIN)))

# Exclude unwanted files from being copied.
RCFILES_CPOUT	:= $(filter-out %.swp,$(RCFILES_CPOUT))
RCFILES_CPOUT	:= $(filter-out %.swo,$(RCFILES_CPOUT))
RCFILES_CPOUT	:= $(filter-out %.pyc,$(RCFILES_CPOUT))

# adjust RCFILES_OUT depending on kernel (i.e. OS)
ifneq ($(KERNEL),linux)
	RCFILES_OUT := $(filter-out $(OUTDIR)/.x%,$(RCFILES_OUT))
	RCFILES_OUT := $(filter-out $(OUTDIR)/.i3/%,$(RCFILES_OUT))
	RCFILES_OUT := $(filter-out $(OUTDIR)/.local/share/applications/%,$(RCFILES_OUT))
endif
ifneq ($(KERNEL),darwin)
	RCFILES_OUT := $(filter-out $(OUTDIR)/.slate%,$(RCFILES_OUT))
endif

### Custom functions ################################################
make_target_dir=@test -d $(@D) || $(MKDIR) $(@D)

### Generic recipes #################################################
$(OUTDIR)/%: $$(subst /.,/_,$(TPLDIR)/%.j2) $(CONFIG) $(wildcard include/*.inc)
	$(make_target_dir)
	@test -d $(@D) || $(MKDIR) $(@D)
	$(J2) $(J2_OPTS) $(<) $(CONFIG) > $(@)

$(OUTDIR)/%: $$(subst /.,/_,$(TPLDIR)/%) $(CONFIG)
	$(make_target_dir)
	$(CP) $(<) $(@)

### Targets #########################################################
.PHONY: all copy-dry copy-real

all: $(RCFILES_OUT) $(RCFILES_CPOUT)

copy-dry: all
	$(RSYNC) --exclude-from=config/exclude.txt $(RSYNC_OPTS) -n $(OUTDIR)/ $(HOME)/

copy-real: all
	$(RSYNC) --exclude-from=config/exclude.txt $(RSYNC_OPTS) $(OUTDIR)/ $(HOME)/

diff: all
	LC_ALL=C $(DIFF) --exclude-from=config/exclude.txt -wr $(HOME)/ $(OUTDIR)/ | $(GREP) -v "^Only in $(HOME)/[^:]*:" || true

clean:
	rm -rf $(OUTDIR)

