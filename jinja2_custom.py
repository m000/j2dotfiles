# -*- coding: utf-8 -*-
import os
import sys
import pipes
from functools import partial

assert sys.version_info >= (2,5), "Need at least Python 2.5."
if sys.version_info < (3,0):
    from shutilwhich import which
else:
    from shutil import which

# Check ansible's extra filters for inspiration:
#   https://github.com/ansible/ansible/tree/devel/lib/ansible/plugins/filter


### Filters #########################################################
def hr(text=None, width=80, fill='#'):
    ''' Creates an ascii horizontal ruler.
    '''
    if text:
        return ('%s %s ' % (3*fill, text)).ljust(width, fill)
    else:
        return ''.ljust(width, fill)


### Tests ###########################################################
def is_dir(d):
    ''' Returns true if d is a directory.
        Tilde and shell variables in d are expanded before testing.
    '''
    if not d:
        return False
    else:
        d = os.path.expandvars(os.path.expanduser(d))
        return os.path.isdir(d)

def is_file(f):
    ''' Returns true if f is a file.
        Tilde and shell variables in f are expanded before testing.
    '''
    if not f:
        return False
    else:
        f = os.path.expandvars(os.path.expanduser(f))
        return os.path.isdir(f)

def is_installed(b):
    ''' Returns true if an executable named b exists in the current path.
    '''
    return True if which(b) else False


### Dictionaries for auto-loading by j2cli ##########################
FILTERS = {
    'hr':               hr,
    'py_type':          type,
    'sh_quote':         pipes.quote,
    'sh_which':         which,
    'path_exists':      os.path.exists,
    'path_expand':      lambda s: os.path.expandvars(os.path.expanduser(s)),
    'path_join':        os.path.join,
    'basename':         os.path.basename,

    'sh_expand':        lambda s: os.path.expandvars(os.path.expanduser(s)),
    'sh_expanduser':    os.path.expanduser,
    'sh_expandvars':    os.path.expandvars,
}
TESTS = {
    'dir':               is_dir,
    'file':              is_file,
    'installed':         is_installed,
}
