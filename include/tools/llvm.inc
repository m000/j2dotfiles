{% import 'include/jinja2_macros.inc' as macros %}
{%- if path.llvm is dir %}
    {% do tools_active.append('llvm') %}
    {% do tools_exports.append(('LLVM_ROOT', '"{0}"'.format(path.llvm))) %}
{%- if shell.use_default_llvm %}
    {% do tools_path.append('"$LLVM_ROOT/bin"') %}
    {% do tools_lpath.append('"$LLVM_ROOT"/lib') %}
{% else %}
    {% do tools_path.insert(0, '"$LLVM_ROOT/bin"') %}
    {% do tools_lpath.insert(0, '"$LLVM_ROOT"/lib') %}
{%- endif -%}
{%- endif -%}
{#-
# vim:ft=sh
-#}
