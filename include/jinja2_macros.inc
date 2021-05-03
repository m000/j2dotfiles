{#
    Creates an argument list from the the specified dict d.
    Order of arguments is not guarantted!
#}
{% macro args_from_dict(d, kpref='-', kvsep=' ') %}
{% for k in d %}{{ kpref }}{{ k }} {{ d[k] }}{{ ' ' if not loop.last }}{% endfor %}
{% endmacro %}

{#
    Runs a command cmd with arguments specified in d.
    Only use this if arguments order does not matter!
#}
{% macro cmd_from_dict(cmd, d, kpref='-', kvsep=' ', require_args=True) %}
{% if d %}
{{ cmd }} {{ args_from_dict(d, kpref, kvsep) }}
{% elif not require_args %}
{{ cmd }}
{% else %}
# {{ '%-40s'|format(cmd) }}# no arguments - command skipped
{% endif %}
{% endmacro %}

{#
    Dumps a list of k, v pairs as environment variable definitions.
    We use a list of pairs rather than a dict to preserve order.
#}
{% macro env_from_list(l, export=True) %}
{% for t in l %}
{{ "export " if export }}{{ t[0] }}={{ t[1] }}
{% endfor %}
{%- endmacro %}

{#
    Emits shell code that updates the contents of path-like shell
    variable varname to include the contents of list l.
    If first_item is found, items before it are prepended to varname.
    Any other items are appended to varname.
    The emitted code avoids having orphan delimiters at the beginning
    or end of the expanded variable.
#}
{% macro pathvar_update(varname, l, delim=':', first_item=None) %}
{% if (not first_item in l) or (first_item in l and l|length > 1) %}
{% with %}
    {% set before = l[0:l.index(first_item)] if first_item in l else [] %}
    {% set after = l[l.index(first_item)+1:] if first_item in l else l %}
	{{-varname}}={{ before | join(delim) -}}
	{%- if before and after -%}
		{{ delim }}"${{ varname }}"${{ '{' + varname }}:+{{ delim + '}' }}
	{%- elif before -%}
		${{ '{' + varname }}:+{{ delim + '}' }}"${{ varname }}"
	{%- elif after -%}
		"${{ varname }}"${{ '{' + varname }}:+{{ delim + '}' }}
	{%- else -%}
		{{ 0/0 }}{# unreachable - throw error just in case #}
	{%- endif -%}
	{{- after | join(delim) }}
{% endwith %}
{% endif %}
{%- endmacro %}
