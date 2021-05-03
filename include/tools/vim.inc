{%- if "vim" is installed -%}
    {% do tools_active.append('vim') %}
    {% do tools_exports.append(('EDITOR', 'vim')) %}
    {% do tools_exports.append(('SVN_EDITOR', 'vim')) %}
{%- endif %}
{#-
# vim:ft=sh
-#}
