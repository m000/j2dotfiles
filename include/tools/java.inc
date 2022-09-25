{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.java is dir -%}
    {% do tools_active.append('java') %}
    {% do tools_exports.append(('JAVA_HOME', '"{0}"'.format(path.java))) %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
