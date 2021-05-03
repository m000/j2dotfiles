{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.gcloud_sdk is dir -%}
    {% do tools_active.append('gcloud_sdk') %}
    {% do tools_path.append('"{0}/bin"'.format(path.gcloud_sdk)) %}
    {% with completion_inc='{0}/completion.{1}.inc'.format(path.gcloud_sdk, shell_type) -%}
        {# XXX: append this to some variable, to be sourced later #}
        {% if completion_inc is file -%}
            source  "{{ completion_inc }}"
        {% endif %}
    {% endwith %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
