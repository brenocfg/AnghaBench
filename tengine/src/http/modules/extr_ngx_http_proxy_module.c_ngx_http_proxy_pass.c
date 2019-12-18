#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_19__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_29__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_34__ {int complete_lengths; int complete_values; int default_port; int uri_part; int no_resolve; TYPE_2__ url; scalar_t__ variables; int /*<<< orphan*/ * values; scalar_t__* lengths; TYPE_8__* source; TYPE_12__* cf; } ;
typedef  TYPE_7__ ngx_url_t ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_35__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_8__ ngx_str_t ;
typedef  TYPE_7__ ngx_http_script_compile_t ;
struct TYPE_33__ {int len; char* data; } ;
struct TYPE_32__ {scalar_t__ len; } ;
struct TYPE_31__ {size_t len; scalar_t__ data; } ;
struct TYPE_27__ {TYPE_5__ uri; TYPE_4__ schema; TYPE_4__ key_start; } ;
struct TYPE_30__ {int /*<<< orphan*/ * upstream; } ;
struct TYPE_24__ {int ssl; TYPE_8__ url; TYPE_6__ location; TYPE_19__ vars; TYPE_3__ upstream; int /*<<< orphan*/  proxy_values; scalar_t__ proxy_lengths; } ;
typedef  TYPE_10__ ngx_http_proxy_loc_conf_t ;
struct TYPE_25__ {int auto_redirect; scalar_t__ noname; scalar_t__ regex; scalar_t__ named; TYPE_6__ name; int /*<<< orphan*/  handler; } ;
typedef  TYPE_11__ ngx_http_core_loc_conf_t ;
struct TYPE_26__ {TYPE_1__* args; } ;
typedef  TYPE_12__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_28__ {TYPE_8__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_11__* ngx_http_conf_get_module_loc_conf (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_proxy_handler ; 
 int /*<<< orphan*/  ngx_http_proxy_set_vars (TYPE_7__*,TYPE_19__*) ; 
 scalar_t__ ngx_http_script_compile (TYPE_7__*) ; 
 scalar_t__ ngx_http_script_variables_count (TYPE_8__*) ; 
 int /*<<< orphan*/ * ngx_http_upstream_add (TYPE_12__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_7__*,int) ; 
 scalar_t__ ngx_strncasecmp (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
ngx_http_proxy_pass(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_proxy_loc_conf_t *plcf = conf;

    size_t                      add;
    u_short                     port;
    ngx_str_t                  *value, *url;
    ngx_url_t                   u;
    ngx_uint_t                  n;
    ngx_http_core_loc_conf_t   *clcf;
    ngx_http_script_compile_t   sc;

    if (plcf->upstream.upstream || plcf->proxy_lengths) {
        return "is duplicate";
    }

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

    clcf->handler = ngx_http_proxy_handler;

    if (clcf->name.len && clcf->name.data[clcf->name.len - 1] == '/') {
        clcf->auto_redirect = 1;
    }

    value = cf->args->elts;

    url = &value[1];

    n = ngx_http_script_variables_count(url);

    if (n) {

        ngx_memzero(&sc, sizeof(ngx_http_script_compile_t));

        sc.cf = cf;
        sc.source = url;
        sc.lengths = &plcf->proxy_lengths;
        sc.values = &plcf->proxy_values;
        sc.variables = n;
        sc.complete_lengths = 1;
        sc.complete_values = 1;

        if (ngx_http_script_compile(&sc) != NGX_OK) {
            return NGX_CONF_ERROR;
        }

#if (NGX_HTTP_SSL)
        plcf->ssl = 1;
#endif

        return NGX_CONF_OK;
    }

    if (ngx_strncasecmp(url->data, (u_char *) "http://", 7) == 0) {
        add = 7;
        port = 80;

    } else if (ngx_strncasecmp(url->data, (u_char *) "https://", 8) == 0) {

#if (NGX_HTTP_SSL)
        plcf->ssl = 1;

        add = 8;
        port = 443;
#else
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "https protocol requires SSL support");
        return NGX_CONF_ERROR;
#endif

    } else {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "invalid URL prefix");
        return NGX_CONF_ERROR;
    }

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.url.len = url->len - add;
    u.url.data = url->data + add;
    u.default_port = port;
    u.uri_part = 1;
    u.no_resolve = 1;

    plcf->upstream.upstream = ngx_http_upstream_add(cf, &u, 0);
    if (plcf->upstream.upstream == NULL) {
        return NGX_CONF_ERROR;
    }

    plcf->vars.schema.len = add;
    plcf->vars.schema.data = url->data;
    plcf->vars.key_start = plcf->vars.schema;

    ngx_http_proxy_set_vars(&u, &plcf->vars);

    plcf->location = clcf->name;

    if (clcf->named
#if (NGX_PCRE)
        || clcf->regex
#endif
        || clcf->noname)
    {
        if (plcf->vars.uri.len) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "\"proxy_pass\" cannot have URI part in "
                               "location given by regular expression, "
                               "or inside named location, "
                               "or inside \"if\" statement, "
                               "or inside \"limit_except\" block");
            return NGX_CONF_ERROR;
        }

        plcf->location.len = 0;
    }

    plcf->url = *url;

    return NGX_CONF_OK;
}