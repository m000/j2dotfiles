{% import 'include/jinja2_macros.inc' as macros %}
{% with -%}
{%- set tools_active=[] -%}
{%- set tools_exports=[] -%}

{# lists for path-like variables contain an initial element to support prepending and appending #}
{%- set tools_path=[None,] -%}
{%- set tools_lpath=[None,] -%}
{%- set tools_manpath=[None,] -%}
{%- set tools_infopath=[None,] -%}

# Tools setup.
{% include 'include/tools/ffmpeg.inc' %}
{% include 'include/tools/gcloud_sdk.inc' %}
{% include 'include/tools/golang.inc' %}
{% include 'include/tools/intel_pin.inc' %}
{% include 'include/tools/java.inc' %}
{% include 'include/tools/llvm.inc' %}
{% include 'include/tools/nodejs.inc' %}
{% include 'include/tools/nvim.inc' %}
{% include 'include/tools/ocaml.inc' %}
{% include 'include/tools/perl5.inc' %}
{% include 'include/tools/rupa_z.inc' %}
{% include 'include/tools/rust.inc' %}
{% include 'include/tools/texlive.inc' %}
{% include 'include/tools/vim.inc' %}

{% if "$HOME/.local/bin" is dir -%}
# Local binaries.
{% do tools_path.insert(0, '"$HOME/.local/bin"') %}
{%- endif -%}

# Active tools in order: {{ tools_active }}
{{ macros.env_from_list(tools_exports) -}}
{{ macros.pathvar_update("PATH", tools_path) -}}
{{ macros.pathvar_update("LD_LIBRARY_PATH", tools_lpath) -}}
{{ macros.pathvar_update("MANPATH", tools_manpath) -}}
{{ macros.pathvar_update("INFOPATH", tools_infopath) -}}
{% endwith %}

{#-
# vim:ft=sh
-#}
