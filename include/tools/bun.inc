{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.bun is dir -%}
    {% do tools_active.append('bun') %}
    {% do tools_exports.append(('BUN_INSTALL', '"{0}"'.format(path.bun))) %}
    {% do tools_path.append('"$BUN_INSTALL/bin"') %}
    {% with completion_inc='{0}/_bun'.format(path.bun) -%}
        {# XXX: append this to some variable, to be sourced later #}
        {% if completion_inc is file -%}
            source  "{{ completion_inc }}"
        {% endif %}
    {% endwith %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
