{% import 'include/jinja2_macros.inc' as macros %}
{{ "Influential environment variables" | hr }}
### path
{# To build the PATH environment variable we create a list which we then join and print.  #}
{% with -%}
    {%- set path_env=['"$PATH"',] -%}
    {%- set exports=[] -%}

    {#- Add /sbin to path - contains ifconfig -#}
    {%- if os.type == "linux" -%}
        {%- do path_env.append('/sbin') -%}
    {%- endif -%}

    {%- if path.homebrew is dir -%}
        {%- do exports.append(('HOMEBREW_PATH', '"{0}/bin":"{0}/sbin":"{0}/share/npm/bin"'.format(path.homebrew))) -%}
        {%- do path_env.insert(0, '"$HOMEBREW_PATH"') -%}
    {%- endif -%}

    {#- Homebrew gnubin -#}
    {%- if path.homebrew is dir and path.homebrew_gnubin -%}
        {%- set gnubin=[] -%}
        {%- for p in path.homebrew_gnubin -%}
            {%- if (path.homebrew + '/opt/' + p + '/libexec/gnubin') is dir -%}
                {%- do gnubin.insert(0, path.homebrew + '/opt/' + p + '/libexec/gnubin') -%}
            {%- endif -%}
        {%- endfor -%}
    {%- endif -%}
    {%- if gnubin -%}
        {%- do exports.append(('HOMEBREW_GNUBIN', gnubin|join(':'))) -%}
        {%- do path_env.insert(0, '"$HOMEBREW_GNUBIN"') -%}
    {%- endif -%}

    {#- Homebrew Ruby -#}
    {%- if [path.homebrew, 'opt/ruby/bin'] | path_join is dir -%}
        {%- do exports.append(('HOMEBREW_RUBYBIN', [path.homebrew, 'opt/ruby/bin'] | path_join | sh_quote)) -%}
        {%- do path_env.insert(0, '"$HOMEBREW_RUBYBIN"') -%}
    {%- endif -%}

    {#- Homebrew curl -#}
    {%- if [path.homebrew, 'opt/curl/bin'] | path_join is dir -%}
        {%- do exports.append(('HOMEBREW_CURLBIN', [path.homebrew, 'opt/curl/bin'] | path_join | sh_quote)) -%}
        {%- do path_env.insert(0, '"$HOMEBREW_CURLBIN"') -%}
    {%- endif -%}

    {#- Home bin -#}
    {%- if "$HOME/bin" is dir -%}
        {%- do path_env.append('"$HOME"/bin') -%}
    {%- endif -%}

    {#- Cliutils -#}
    {%- if path.cliutils is dir -%}
        {%- do path_env.append('"%s"/bin' % (path.cliutils)) -%}
    {%- endif -%}

    {#- Output exports and PATH #}
{%- for k, v in exports -%}
export {{k}}={{v}}
{% endfor -%}
export PATH={{ path_env|join(':') }}
{%- endwith %}

### other stuff

{{ "OS-specific environment settings for %s" | format(os.type) | hr }}
{% if os.type == "osx" -%}
{%- if [path.homebrew, 'opt/curl/bin'] | path_join is dir -%}
export HOMEBREW_FORCE_BREWED_CURL=yes
{% endif %}
{%- if [path.homebrew, 'opt/openssl@1.1'] | path_join is dir -%}
export RUBY_CONFIGURE_OPTS="--with-openssl-dir='$(brew --prefix openssl@1.1)'"
{% endif %}
{% endif %}

{{ "Host-specific environment settings for %s" | format(hostid) | hr }}
{{ macros.cmd_from_dict('ulimit', shell.ulimit) }}
{{- macros.env_from_list(shell.env) }}

{#-
# vim:ft=sh
-#}
