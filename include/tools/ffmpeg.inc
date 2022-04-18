{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.ffmpeg is dir -%}
    {% do tools_active.append('ffmpeg') %}
    {% do tools_path.append(path.ffmpeg) %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
