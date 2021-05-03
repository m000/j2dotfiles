{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.texlive is dir -%}
    {% do tools_active.append('texlive') %}
    {% do tools_exports.append(('TEXLIVE', '"{0}"'.format(path.texlive))) %}
    {% do tools_path.insert(0, '"$TEXLIVE/bin/x86_64-linux"') %}
    {% do tools_manpath.insert(0, '"$TEXLIVE/texmf-dist/doc/man"') %}
    {% do tools_infopath.insert(0, '"$TEXLIVE/texmf-dist/doc/info"') %}
{%- endif %}
{#-
# vim:ft=sh
-#}
