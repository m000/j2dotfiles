{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.nvim is dir -%}
    {% do tools_active.append('nvim') %}
    {% do tools_path.insert(0, '"{0}/bin"'.format(path.nvim)) %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
