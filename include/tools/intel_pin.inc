{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.intel_pin is dir -%}
    {% do tools_active.append('intel_pin') %}
    {% do tools_exports.append(('PIN_ROOT', '"{0}"'.format(path.intel_pin))) %}
    {% do tools_path.append('"$PIN_ROOT"') %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
