{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.nodejs is dir -%}
    {% do tools_active.append('nodejs') %}
    {% do tools_exports.append(('NODEJS_ROOT', '"{0}"'.format(path.nodejs))) %}
    {% do tools_path.append('"$NODEJS_ROOT/bin"') %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
