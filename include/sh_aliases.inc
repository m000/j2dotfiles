{{ "Generic aliases" | hr }}
### job control
alias STOP='killall -STOP'
alias CONT='killall -CONT'
### text manipulation
alias lnmerge="tr '\n' ' '"
alias titlecase="sed -r 's/((^|[[:blank:]])[[:alpha:]])([[:alpha:]]*)/\U\1\L\3/g'"
alias sigmafix="sed -r 's/σ([^[:alpha:]]|$)/ς\1'/g"
### program-specific shorthands
alias gvimt='gvim --remote-tab'
alias nyancat='telnet nyancat.dakko.us'
alias svnup='svn up --ignore-externals'
alias ts='date +"%Y-%m-%d %H:%M:%S"'
alias vi=vim
{% if 'subl' is installed -%}
{# on mac: sudo ln -s "/Applications/Sublime Text.app/Contents/SharedSupport/bin/subl" /usr/local/bin/ #}
alias slt="subl -a"
{% endif %}
### misc
{% if "python3" is installed %}
alias uuid4='python3 -c "import uuid; print(uuid.uuid4())"'
alias json2yaml="python3 -c 'import json, sys, ruamel.yaml as Y; Y.YAML().dump(json.load(sys.stdin), sys.stdout)'"
alias yaml2json="python3 -c 'import json, os, sys, ruamel.yaml as Y; print(json.dumps(Y.YAML(typ=\"safe\").load(sys.stdin), indent=int(os.getenv(\"JSON_INDENT\") or 2)))'"
{% endif %}
alias jsonl2json='awk '\''BEGIN{print "["} {printf("%s%s", (NR > 1 ? ",\n" : ""), $0)} END{ print "\n]"}'\'

{{ "OS-specific aliases for %s" | format(os.type) | hr }}
{% if os.type == "osx" -%}
alias ldd='otool -L'
alias ls='ls --color=tty'
alias m='make -j $(sysctl -n hw.ncpu)'
alias top='top -o cpu'
{%- elif os.type == "linux" %}
{%- if 'xdg-open' is installed -%}
alias open="xdg-open"
{% endif -%}
alias m='make -j $(nproc)'
{%- elif os.type == "bsd" %}
alias make=gmake
{%- endif %}

{{ "Host-specific aliases for %s" | format(hostid) | hr }}
{% if hostid == "The-Shrine-osx" -%}
alias tagit="open -a 'The Tagger'"
alias xpra="/Applications/Xpra.app/Contents/MacOS/Xpra"
{%- else -%}
# nothing yet!
{%- endif %}

{#
# vim:ft=sh
-#}
