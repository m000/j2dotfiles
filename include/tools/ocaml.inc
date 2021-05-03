{% import 'include/jinja2_macros.inc' as macros %}
{% if ["opam",] is installed and path.ocaml_opam is dir %}
	{# contents recreated based on the output of opam env #}
	{% do tools_active.append('ocaml') %}
	{% do tools_exports.append(('OPAMROOT', '"{0}"'.format(path.ocaml_opam))) %}
	{% do tools_exports.append(('OPAM_SWITCH_PREFIX', '"$OPAMROOT/default"')) %}
	{% do tools_exports.append(('CAML_LD_LIBRARY_PATH', '"$OPAM_SWITCH_PREFIX/lib/stublibs"')) %}
	{% do tools_exports.append(('OCAML_TOPLEVEL_PATH', '"$OPAM_SWITCH_PREFIX/lib/toplevel"')) %}
	{% do tools_manpath.insert(0, '"$OPAM_SWITCH_PREFIX/man"') %}
	{% do tools_path.insert(0, '"$OPAM_SWITCH_PREFIX/bin"') %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
