{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.golang is dir -%}
    {% do tools_active.append('golang') %}
    {% do tools_exports.append(('GOLANG_ROOT', '"{0}"'.format(path.golang))) %}
    {% do tools_path.append('"$GOLANG_ROOT/bin"') %}
{%- endif -%}
{%- if path.golang_workspace is dir -%}
    {% do tools_exports.append(('GOPATH', '"{0}"'.format(path.golang_workspace))) %}
    {% do tools_path.append('"$GOPATH/bin"') %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
