#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;
typedef  struct TYPE_20__   TYPE_12__ ;

/* Type definitions */
struct TYPE_25__ {int no_resolve; int no_port; int /*<<< orphan*/  host; } ;
typedef  TYPE_4__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_26__ {TYPE_19__* servers; struct TYPE_26__** srv_conf; } ;
typedef  TYPE_5__ ngx_http_upstream_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_server_t ;
struct TYPE_27__ {void* (* create_loc_conf ) (TYPE_8__*) ;void* (* create_srv_conf ) (TYPE_8__*) ;} ;
typedef  TYPE_6__ ngx_http_module_t ;
struct TYPE_28__ {void** loc_conf; TYPE_5__** srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_7__ ngx_http_conf_ctx_t ;
struct TYPE_29__ {int /*<<< orphan*/  cmd_type; TYPE_7__* ctx; int /*<<< orphan*/  pool; TYPE_3__* cycle; TYPE_1__* args; } ;
typedef  TYPE_8__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_24__ {TYPE_2__** modules; } ;
struct TYPE_23__ {scalar_t__ type; size_t ctx_index; TYPE_6__* ctx; } ;
struct TYPE_22__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_21__ {scalar_t__ nelts; } ;
struct TYPE_20__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_HTTP_MODULE ; 
 int NGX_HTTP_UPSTREAM_BACKUP ; 
 int NGX_HTTP_UPSTREAM_CREATE ; 
 int NGX_HTTP_UPSTREAM_DOWN ; 
 int NGX_HTTP_UPSTREAM_FAIL_TIMEOUT ; 
 int NGX_HTTP_UPSTREAM_MAX_CONNS ; 
 int NGX_HTTP_UPSTREAM_MAX_FAILS ; 
 int NGX_HTTP_UPSTREAM_WEIGHT ; 
 int /*<<< orphan*/  NGX_HTTP_UPS_CONF ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 TYPE_19__* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 char* ngx_conf_parse (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int ngx_http_max_module ; 
 TYPE_5__* ngx_http_upstream_add (TYPE_8__*,TYPE_4__*,int) ; 
 TYPE_12__ ngx_http_upstream_module ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 void* stub1 (TYPE_8__*) ; 
 void* stub2 (TYPE_8__*) ; 

__attribute__((used)) static char *
ngx_http_upstream(ngx_conf_t *cf, ngx_command_t *cmd, void *dummy)
{
    char                          *rv;
    void                          *mconf;
    ngx_str_t                     *value;
    ngx_url_t                      u;
    ngx_uint_t                     m;
    ngx_conf_t                     pcf;
    ngx_http_module_t             *module;
    ngx_http_conf_ctx_t           *ctx, *http_ctx;
    ngx_http_upstream_srv_conf_t  *uscf;

    ngx_memzero(&u, sizeof(ngx_url_t));

    value = cf->args->elts;
    u.host = value[1];
    u.no_resolve = 1;
    u.no_port = 1;

    uscf = ngx_http_upstream_add(cf, &u, NGX_HTTP_UPSTREAM_CREATE
                                         |NGX_HTTP_UPSTREAM_WEIGHT
                                         |NGX_HTTP_UPSTREAM_MAX_CONNS
                                         |NGX_HTTP_UPSTREAM_MAX_FAILS
                                         |NGX_HTTP_UPSTREAM_FAIL_TIMEOUT
                                         |NGX_HTTP_UPSTREAM_DOWN
                                         |NGX_HTTP_UPSTREAM_BACKUP);
    if (uscf == NULL) {
        return NGX_CONF_ERROR;
    }


    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_http_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    http_ctx = cf->ctx;
    ctx->main_conf = http_ctx->main_conf;

    /* the upstream{}'s srv_conf */

    ctx->srv_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_http_max_module);
    if (ctx->srv_conf == NULL) {
        return NGX_CONF_ERROR;
    }

    ctx->srv_conf[ngx_http_upstream_module.ctx_index] = uscf;

    uscf->srv_conf = ctx->srv_conf;


    /* the upstream{}'s loc_conf */

    ctx->loc_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_http_max_module);
    if (ctx->loc_conf == NULL) {
        return NGX_CONF_ERROR;
    }

    for (m = 0; cf->cycle->modules[m]; m++) {
        if (cf->cycle->modules[m]->type != NGX_HTTP_MODULE) {
            continue;
        }

        module = cf->cycle->modules[m]->ctx;

        if (module->create_srv_conf) {
            mconf = module->create_srv_conf(cf);
            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->srv_conf[cf->cycle->modules[m]->ctx_index] = mconf;
        }

        if (module->create_loc_conf) {
            mconf = module->create_loc_conf(cf);
            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->loc_conf[cf->cycle->modules[m]->ctx_index] = mconf;
        }
    }

    uscf->servers = ngx_array_create(cf->pool, 4,
                                     sizeof(ngx_http_upstream_server_t));
    if (uscf->servers == NULL) {
        return NGX_CONF_ERROR;
    }


    /* parse inside upstream{} */

    pcf = *cf;
    cf->ctx = ctx;
    cf->cmd_type = NGX_HTTP_UPS_CONF;

    rv = ngx_conf_parse(cf, NULL);

    *cf = pcf;

    if (rv != NGX_CONF_OK) {
        return rv;
    }

    if (uscf->servers->nelts == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "no servers are inside upstream");
        return NGX_CONF_ERROR;
    }

    return rv;
}