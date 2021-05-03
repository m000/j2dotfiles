{%- if path.rupa_z is file -%}
{# z - https://github.com/rupa/z #}
source {{ path.rupa_z | sh_quote }}
{%- endif -%}
