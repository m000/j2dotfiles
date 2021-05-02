# j2dotfiles

A simple solution to keep track of your dot files and quickly deploy a uniform,
yet customizable environment on different hosts.

## How it works
j2dotfiles compiles the dot files from [Jinja2](http://jinja.pocoo.org/)
templates and host-specific configuration files.
Jinja2 is invoked via the [j2cli](https://github.com/m000/j2cli)<sup>1</sup>
command-line wrapper.
The dot files templates are first rendered in a local directory
(default: `output`) and then copied to your home directory using
[rsync](https://rsync.samba.org/). This allows for inspection of
changes before overwritting your current set of dot files.
The process is automated using [GNU Make](https://www.gnu.org/software/make/).

## How to use it

### New host
python3
python3-virtualenv
python3-pip
zsh
jq ?
git


TBA
```
apt-get install zsh git openssh-client python3-virtualenv jq make

ssh-keygen -t ed25519

virtualenv -p python3 pyenv
. ./pyenv/bin/activate
pip install -r requirements.txt 

make

vi config/...

make

install ohmyzsh

run
```


### Python environment
Install the required Python packages in a local environment:
```
virtualenv .dotfiles_pyenv
. ./.dotfiles_pyenv/bin/activate
pip install -r requirements.txt
```

Then each time you want to update your dot files, you only
need to activate the environment:
```
. ./.dotfiles_pyenv/bin/activate
```

### Common Makefile targets
* **all**: Compile all dot files in the output dir.
* **clean**: Remove the output dir and all its contents.
* **copy-dry**: See what files will be copied to your home directory.
* **copy-real**: Copy the generated files to your home directory.
* **diff**: See the differences between generated and installed dot files.

<sup>1</sup> [j2cli](https://github.com/kolypto/j2cli)

### Resources
* [Jinja2 Template Designer Documentation](http://jinja.pocoo.org/docs/dev/templates/)
