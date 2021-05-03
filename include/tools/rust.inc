{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.rust_cargo is dir -%}
    {% do tools_active.append('rust') %}
    {% do tools_exports.append(('CARGO_HOME', '"{0}"'.format(path.rust_cargo))) %}
    {% do tools_path.insert(0, '"$CARGO_HOME/bin"') %}
{%- endif -%}
{%- if path.rust_rustup is dir -%}
    {% do tools_exports.append(('RUSTUP_HOME', '"{0}"'.format(path.rust_rustup))) %}
{%- endif -%}
{#-
# vim:ft=sh
-#}
