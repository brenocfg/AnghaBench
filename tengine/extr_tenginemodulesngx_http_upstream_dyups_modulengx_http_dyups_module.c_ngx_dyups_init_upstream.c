#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_21__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_34__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_33__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_35__ {int flags; int /*<<< orphan*/  ref; struct TYPE_35__** srv_conf; scalar_t__ port; scalar_t__ line; int /*<<< orphan*/ * file_name; TYPE_2__ host; } ;
typedef  TYPE_4__ ngx_http_upstream_srv_conf_t ;
struct TYPE_31__ {TYPE_4__** elts; } ;
struct TYPE_36__ {TYPE_1__ upstreams; } ;
typedef  TYPE_5__ ngx_http_upstream_main_conf_t ;
struct TYPE_37__ {void* (* create_srv_conf ) (TYPE_10__*) ;} ;
typedef  TYPE_6__ ngx_http_module_t ;
typedef  TYPE_4__ ngx_http_dyups_upstream_srv_conf_t ;
struct TYPE_38__ {int dynamic; scalar_t__ deleted; TYPE_9__* ctx; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * pool; TYPE_4__* upstream; } ;
typedef  TYPE_8__ ngx_http_dyups_srv_conf_t ;
struct TYPE_39__ {TYPE_4__** srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_9__ ngx_http_conf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
struct TYPE_25__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/ * cycle; scalar_t__ ctx; int /*<<< orphan*/  cmd_type; scalar_t__ module_type; } ;
typedef  TYPE_10__ ngx_conf_t ;
struct TYPE_32__ {scalar_t__ index; } ;
struct TYPE_30__ {scalar_t__* conf_ctx; int /*<<< orphan*/  log; } ;
struct TYPE_29__ {size_t ctx_index; } ;
struct TYPE_28__ {size_t index; } ;
struct TYPE_27__ {size_t ctx_index; } ;
struct TYPE_26__ {scalar_t__ type; scalar_t__ index; size_t ctx_index; TYPE_6__* ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_MAIN_CONF ; 
 scalar_t__ NGX_HTTP_MODULE ; 
 int NGX_HTTP_UPSTREAM_BACKUP ; 
 int NGX_HTTP_UPSTREAM_CREATE ; 
 int NGX_HTTP_UPSTREAM_DOWN ; 
 int NGX_HTTP_UPSTREAM_FAIL_TIMEOUT ; 
 int NGX_HTTP_UPSTREAM_MAX_FAILS ; 
 int NGX_HTTP_UPSTREAM_WEIGHT ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ ) ; 
 TYPE_19__* ngx_cycle ; 
 TYPE_21__ ngx_http_core_module ; 
 TYPE_5__* ngx_http_cycle_get_module_main_conf (TYPE_19__*,TYPE_15__) ; 
 TYPE_17__ ngx_http_dyups_module ; 
 int ngx_http_max_module ; 
 TYPE_16__ ngx_http_module ; 
 TYPE_15__ ngx_http_upstream_module ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_10__*,int) ; 
 TYPE_13__** ngx_modules ; 
 void* ngx_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_pstrdup (int /*<<< orphan*/ *,TYPE_3__*) ; 
 void* stub1 (TYPE_10__*) ; 

__attribute__((used)) static ngx_int_t
ngx_dyups_init_upstream(ngx_http_dyups_srv_conf_t *duscf, ngx_str_t *name,
    ngx_uint_t index)
{
    void                                *mconf;
    ngx_uint_t                           m;
    ngx_conf_t                           cf;
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
    /* TODO */
    /* uscf->default_port = 0; */

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

    for (m = 0; ngx_modules[m]; m++) {
        if (ngx_modules[m]->type != NGX_HTTP_MODULE) {
            continue;
        }

        if (ngx_modules[m]->index == ngx_http_core_module.index) {
            continue;
        }

        module = ngx_modules[m]->ctx;

        if (module->create_srv_conf) {
            mconf = module->create_srv_conf(&cf);
            if (mconf == NULL) {
                return NGX_ERROR;
            }

            ctx->srv_conf[ngx_modules[m]->ctx_index] = mconf;
        }
    }

    dscf = uscf->srv_conf[ngx_http_dyups_module.ctx_index];
    duscf->ref = &dscf->ref;
    duscf->ctx = ctx;
    duscf->deleted = 0;

#if (NGX_HTTP_UPSTREAM_RBTREE)
    uscf->node.key = ngx_crc32_short(uscf->host.data, uscf->host.len);

    ngx_rbtree_insert(&umcf->rbtree, &uscf->node);
#endif

    return NGX_OK;
}