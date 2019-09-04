#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_23__ {char* (* merge_srv_conf ) (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;char* (* merge_loc_conf ) (TYPE_8__*,TYPE_6__*,TYPE_6__*) ;} ;
typedef  TYPE_3__ ngx_http_module_t ;
struct TYPE_24__ {TYPE_2__* ctx; } ;
typedef  TYPE_4__ ngx_http_core_srv_conf_t ;
struct TYPE_21__ {size_t nelts; TYPE_4__** elts; } ;
struct TYPE_25__ {TYPE_1__ servers; } ;
typedef  TYPE_5__ ngx_http_core_main_conf_t ;
struct TYPE_26__ {int /*<<< orphan*/  locations; } ;
typedef  TYPE_6__ ngx_http_core_loc_conf_t ;
struct TYPE_27__ {TYPE_6__** loc_conf; int /*<<< orphan*/ * srv_conf; } ;
typedef  TYPE_7__ ngx_http_conf_ctx_t ;
struct TYPE_28__ {scalar_t__ ctx; } ;
typedef  TYPE_8__ ngx_conf_t ;
struct TYPE_22__ {TYPE_6__** loc_conf; int /*<<< orphan*/ * srv_conf; } ;
struct TYPE_20__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 TYPE_19__ ngx_http_core_module ; 
 char* ngx_http_merge_locations (TYPE_8__*,int /*<<< orphan*/ ,TYPE_6__**,TYPE_3__*,size_t) ; 
 char* stub1 (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub2 (TYPE_8__*,TYPE_6__*,TYPE_6__*) ; 

__attribute__((used)) static char *
ngx_http_merge_servers(ngx_conf_t *cf, ngx_http_core_main_conf_t *cmcf,
    ngx_http_module_t *module, ngx_uint_t ctx_index)
{
    char                        *rv;
    ngx_uint_t                   s;
    ngx_http_conf_ctx_t         *ctx, saved;
    ngx_http_core_loc_conf_t    *clcf;
    ngx_http_core_srv_conf_t   **cscfp;

    cscfp = cmcf->servers.elts;
    ctx = (ngx_http_conf_ctx_t *) cf->ctx;
    saved = *ctx;
    rv = NGX_CONF_OK;

    for (s = 0; s < cmcf->servers.nelts; s++) {

        /* merge the server{}s' srv_conf's */

        ctx->srv_conf = cscfp[s]->ctx->srv_conf;

        if (module->merge_srv_conf) {
            rv = module->merge_srv_conf(cf, saved.srv_conf[ctx_index],
                                        cscfp[s]->ctx->srv_conf[ctx_index]);
            if (rv != NGX_CONF_OK) {
                goto failed;
            }
        }

        if (module->merge_loc_conf) {

            /* merge the server{}'s loc_conf */

            ctx->loc_conf = cscfp[s]->ctx->loc_conf;

            rv = module->merge_loc_conf(cf, saved.loc_conf[ctx_index],
                                        cscfp[s]->ctx->loc_conf[ctx_index]);
            if (rv != NGX_CONF_OK) {
                goto failed;
            }

            /* merge the locations{}' loc_conf's */

            clcf = cscfp[s]->ctx->loc_conf[ngx_http_core_module.ctx_index];

            rv = ngx_http_merge_locations(cf, clcf->locations,
                                          cscfp[s]->ctx->loc_conf,
                                          module, ctx_index);
            if (rv != NGX_CONF_OK) {
                goto failed;
            }
        }
    }

failed:

    *ctx = saved;

    return rv;
}