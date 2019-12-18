#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_9__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_23__ ;
typedef  struct TYPE_35__   TYPE_21__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_38__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_39__ {scalar_t__ type; scalar_t__ index; size_t ctx_index; TYPE_7__* ctx; } ;
typedef  TYPE_4__ ngx_module_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_37__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_40__ {int flags; int /*<<< orphan*/  ref; struct TYPE_40__** srv_conf; scalar_t__ default_port; scalar_t__ port; scalar_t__ line; int /*<<< orphan*/ * file_name; TYPE_2__ host; } ;
typedef  TYPE_5__ ngx_http_upstream_srv_conf_t ;
struct TYPE_34__ {TYPE_5__** elts; } ;
struct TYPE_41__ {TYPE_1__ upstreams; } ;
typedef  TYPE_6__ ngx_http_upstream_main_conf_t ;
struct TYPE_42__ {TYPE_5__* (* create_srv_conf ) (TYPE_11__*) ;} ;
typedef  TYPE_7__ ngx_http_module_t ;
typedef  TYPE_5__ ngx_http_dyups_upstream_srv_conf_t ;
struct TYPE_43__ {int dynamic; scalar_t__ deleted; TYPE_10__* ctx; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * pool; TYPE_5__* upstream; } ;
typedef  TYPE_9__ ngx_http_dyups_srv_conf_t ;
struct TYPE_29__ {TYPE_5__** srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_10__ ngx_http_conf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
struct TYPE_30__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/ * cycle; scalar_t__ ctx; int /*<<< orphan*/  cmd_type; scalar_t__ module_type; } ;
typedef  TYPE_11__ ngx_conf_t ;
struct TYPE_36__ {scalar_t__ index; } ;
struct TYPE_35__ {TYPE_4__** modules; scalar_t__* conf_ctx; int /*<<< orphan*/  log; } ;
struct TYPE_33__ {size_t ctx_index; } ;
struct TYPE_32__ {size_t index; } ;
struct TYPE_31__ {size_t ctx_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_MAIN_CONF ; 
 scalar_t__ NGX_HTTP_MODULE ; 
 int NGX_HTTP_UPSTREAM_BACKUP ; 
 int NGX_HTTP_UPSTREAM_CREATE ; 
 int NGX_HTTP_UPSTREAM_DOWN ; 
 int NGX_HTTP_UPSTREAM_FAIL_TIMEOUT ; 
 int NGX_HTTP_UPSTREAM_MAX_CONNS ; 
 int NGX_HTTP_UPSTREAM_MAX_FAILS ; 
 int NGX_HTTP_UPSTREAM_WEIGHT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ ) ; 
 TYPE_21__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_dyups_add_upstream_top_filter (TYPE_6__*,TYPE_5__*) ; 
 TYPE_23__ ngx_http_core_module ; 
 TYPE_6__* ngx_http_cycle_get_module_main_conf (TYPE_21__*,TYPE_17__) ; 
 TYPE_19__ ngx_http_dyups_module ; 
 int ngx_http_max_module ; 
 TYPE_18__ ngx_http_module ; 
 TYPE_17__ ngx_http_upstream_module ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_11__*,int) ; 
 TYPE_4__** ngx_modules ; 
 void* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_pstrdup (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_5__* stub1 (TYPE_11__*) ; 

__attribute__((used)) static ngx_int_t
ngx_dyups_init_upstream(ngx_http_dyups_srv_conf_t *duscf, ngx_str_t *name,
    ngx_uint_t index)
{
    ngx_uint_t                           mi, m;
    ngx_conf_t                           cf;
    ngx_module_t                        **modules;
    ngx_http_module_t                   *module;
    ngx_http_conf_ctx_t                 *ctx;
    ngx_http_upstream_srv_conf_t        *uscf, **uscfp;
    ngx_http_upstream_main_conf_t       *umcf;
    ngx_http_dyups_upstream_srv_conf_t  *dscf;

    umcf = ngx_http_cycle_get_module_main_conf(ngx_cycle,
                                               ngx_http_upstream_module);
    uscfp = umcf->upstreams.elts;

    duscf->pool = ngx_create_pool(512, ngx_cycle->log);
    if (duscf->pool == NULL) {
        return NGX_ERROR;
    }

    uscf = ngx_pcalloc(duscf->pool, sizeof(ngx_http_upstream_srv_conf_t));
    if (uscf == NULL) {
        return NGX_ERROR;
    }

    uscf->flags = NGX_HTTP_UPSTREAM_CREATE
                 |NGX_HTTP_UPSTREAM_WEIGHT
#ifdef NGX_HTTP_UPSTREAM_MAX_CONNS
                 |NGX_HTTP_UPSTREAM_MAX_CONNS
#endif
                 |NGX_HTTP_UPSTREAM_MAX_FAILS
                 |NGX_HTTP_UPSTREAM_FAIL_TIMEOUT
                 |NGX_HTTP_UPSTREAM_DOWN
                 |NGX_HTTP_UPSTREAM_BACKUP;

    uscf->host.data = ngx_pstrdup(duscf->pool, name);
    if (uscf->host.data == NULL) {
        return NGX_ERROR;
    }

    uscf->host.len = name->len;
    uscf->file_name = (u_char *) "dynamic_upstream";
    uscf->line = 0;
    uscf->port = 0;
#if nginx_version < 1011006
    uscf->default_port = 0;
#endif
    uscfp[index] = uscf;

    duscf->dynamic = 1;
    duscf->upstream = uscf;

    ngx_memzero(&cf, sizeof(ngx_conf_t));
    cf.module_type = NGX_HTTP_MODULE;
    cf.cmd_type = NGX_HTTP_MAIN_CONF;
    cf.pool = duscf->pool;
    cf.ctx = ngx_cycle->conf_ctx[ngx_http_module.index];
    cf.cycle = (ngx_cycle_t *) ngx_cycle;

    ctx = ngx_pcalloc(duscf->pool, sizeof(ngx_http_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ctx->main_conf = ((ngx_http_conf_ctx_t *)
                      ngx_cycle->conf_ctx[ngx_http_module.index])->main_conf;

    ctx->srv_conf = ngx_pcalloc(cf.pool, sizeof(void *) * ngx_http_max_module);
    if (ctx->srv_conf == NULL) {
        return NGX_ERROR;
    }

    ctx->srv_conf[ngx_http_upstream_module.ctx_index] = uscf;
    uscf->srv_conf = ctx->srv_conf;

#if nginx_version >= 1009011
    modules = ngx_cycle->modules;
#else
    modules = ngx_modules;
#endif

    for (m = 0; modules[m]; m++) {
        if (modules[m]->type != NGX_HTTP_MODULE) {
            continue;
        }

        if (modules[m]->index == ngx_http_core_module.index) {
            continue;
        }

        module = modules[m]->ctx;
        mi = modules[m]->ctx_index;

        if (module->create_srv_conf) {
            ctx->srv_conf[mi] = module->create_srv_conf(&cf);
            if (ctx->srv_conf[mi] == NULL) {
                return NGX_ERROR;
            }
        }
    }

    dscf = uscf->srv_conf[ngx_http_dyups_module.ctx_index];
    duscf->ref = &dscf->ref;
    duscf->ctx = ctx;
    duscf->deleted = 0;

    ngx_dyups_add_upstream_top_filter(umcf, uscf);

    return NGX_OK;
}