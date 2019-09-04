#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_24__ {int /*<<< orphan*/ * ctx; } ;
struct TYPE_32__ {int /*<<< orphan*/ * certificates; TYPE_14__ ssl; int /*<<< orphan*/  stapling; } ;
typedef  TYPE_6__ ngx_http_ssl_srv_conf_t ;
struct TYPE_33__ {int /*<<< orphan*/  line; int /*<<< orphan*/  file_name; TYPE_5__* ctx; } ;
typedef  TYPE_7__ ngx_http_core_srv_conf_t ;
struct TYPE_27__ {size_t nelts; TYPE_7__** elts; } ;
struct TYPE_34__ {TYPE_2__* ports; TYPE_1__ servers; } ;
typedef  TYPE_8__ ngx_http_core_main_conf_t ;
struct TYPE_35__ {int /*<<< orphan*/  resolver_timeout; int /*<<< orphan*/  resolver; } ;
typedef  TYPE_9__ ngx_http_core_loc_conf_t ;
struct TYPE_29__ {size_t nelts; TYPE_11__* elts; } ;
struct TYPE_21__ {TYPE_3__ addrs; } ;
typedef  TYPE_10__ ngx_http_conf_port_t ;
struct TYPE_30__ {int /*<<< orphan*/  ssl; } ;
struct TYPE_22__ {TYPE_7__* default_server; TYPE_4__ opt; } ;
typedef  TYPE_11__ ngx_http_conf_addr_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_12__ ngx_conf_t ;
struct TYPE_31__ {TYPE_6__** srv_conf; TYPE_9__** loc_conf; } ;
struct TYPE_28__ {size_t nelts; TYPE_10__* elts; } ;
struct TYPE_26__ {size_t ctx_index; } ;
struct TYPE_25__ {size_t ctx_index; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 TYPE_8__* ngx_http_conf_get_module_main_conf (TYPE_12__*,TYPE_17__) ; 
 TYPE_17__ ngx_http_core_module ; 
 TYPE_15__ ngx_http_ssl_module ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_ssl_stapling_resolver (TYPE_12__*,TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_ssl_init(ngx_conf_t *cf)
{
    ngx_uint_t                   a, p, s;
    ngx_http_conf_addr_t        *addr;
    ngx_http_conf_port_t        *port;
    ngx_http_ssl_srv_conf_t     *sscf;
    ngx_http_core_loc_conf_t    *clcf;
    ngx_http_core_srv_conf_t   **cscfp, *cscf;
    ngx_http_core_main_conf_t   *cmcf;

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);
    cscfp = cmcf->servers.elts;

    for (s = 0; s < cmcf->servers.nelts; s++) {

        sscf = cscfp[s]->ctx->srv_conf[ngx_http_ssl_module.ctx_index];

        if (sscf->ssl.ctx == NULL || !sscf->stapling) {
            continue;
        }

        clcf = cscfp[s]->ctx->loc_conf[ngx_http_core_module.ctx_index];

        if (ngx_ssl_stapling_resolver(cf, &sscf->ssl, clcf->resolver,
                                      clcf->resolver_timeout)
            != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    if (cmcf->ports == NULL) {
        return NGX_OK;
    }

    port = cmcf->ports->elts;
    for (p = 0; p < cmcf->ports->nelts; p++) {

        addr = port[p].addrs.elts;
        for (a = 0; a < port[p].addrs.nelts; a++) {

            if (!addr[a].opt.ssl) {
                continue;
            }

            cscf = addr[a].default_server;
            sscf = cscf->ctx->srv_conf[ngx_http_ssl_module.ctx_index];

            if (sscf->certificates == NULL) {
                ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                              "no \"ssl_certificate\" is defined for "
                              "the \"listen ... ssl\" directive in %s:%ui",
                              cscf->file_name, cscf->line);
                return NGX_ERROR;
            }
        }
    }

    return NGX_OK;
}