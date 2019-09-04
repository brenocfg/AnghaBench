#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_24__ {int /*<<< orphan*/  timeout; TYPE_7__* data; int /*<<< orphan*/  handler; TYPE_2__ name; } ;
typedef  TYPE_3__ ngx_resolver_ctx_t ;
struct TYPE_25__ {scalar_t__ resolved; int /*<<< orphan*/  log; TYPE_2__* host; } ;
typedef  TYPE_4__ ngx_peer_connection_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_26__ {TYPE_3__* dyn_resolve_ctx; } ;
typedef  TYPE_5__ ngx_http_upstream_t ;
struct TYPE_27__ {int fallback; scalar_t__ fail_check; scalar_t__ fail_timeout; } ;
typedef  TYPE_6__ ngx_http_upstream_dynamic_srv_conf_t ;
struct TYPE_28__ {scalar_t__ (* original_get_peer ) (TYPE_4__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; TYPE_8__* request; TYPE_6__* conf; } ;
typedef  TYPE_7__ ngx_http_upstream_dynamic_peer_data_t ;
struct TYPE_29__ {TYPE_1__* connection; TYPE_5__* upstream; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_30__ {int /*<<< orphan*/  resolver_timeout; int /*<<< orphan*/ * resolver; } ;
typedef  TYPE_9__ ngx_http_core_loc_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ INADDR_NONE ; 
 scalar_t__ NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_HTTP_BAD_GATEWAY ; 
 scalar_t__ NGX_HTTP_UPSTREAM_DR_FAILED ; 
 scalar_t__ NGX_HTTP_UPSTREAM_DR_OK ; 
#define  NGX_HTTP_UPSTREAM_DYN_RESOLVE_SHUTDOWN 129 
#define  NGX_HTTP_UPSTREAM_DYN_RESOLVE_STALE 128 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 TYPE_3__* NGX_NO_RESOLVER ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_YIELD ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_9__* ngx_http_get_module_loc_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_dynamic_handler ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_8__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_inet_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_resolve_name (TYPE_3__*) ; 
 TYPE_3__* ngx_resolve_start (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ ngx_time () ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_get_dynamic_peer(ngx_peer_connection_t *pc, void *data)
{
    ngx_http_upstream_dynamic_peer_data_t  *bp = data;
    ngx_http_request_t                     *r;
    ngx_http_core_loc_conf_t               *clcf;
    ngx_resolver_ctx_t                     *ctx, temp;
    ngx_http_upstream_t                    *u;
    ngx_int_t                               rc;
    ngx_http_upstream_dynamic_srv_conf_t   *dscf;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                   "get dynamic peer");

    /* The "get" function will be called twice if
     * one host is resolved into an IP address.
     * (via 'ngx_http_upstream_connect' if resolved successfully)
     *
     * So here we need to determine if it is the first
     * time call or the second time call.
     */
    if (pc->resolved == NGX_HTTP_UPSTREAM_DR_OK) {
        return NGX_OK;
    }

    dscf = bp->conf;
    r = bp->request;
    u = r->upstream;

    if (pc->resolved == NGX_HTTP_UPSTREAM_DR_FAILED) {

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                       "resolve failed! fallback: %ui", dscf->fallback);

        switch (dscf->fallback) {

        case NGX_HTTP_UPSTREAM_DYN_RESOLVE_STALE:
            return NGX_OK;

        case NGX_HTTP_UPSTREAM_DYN_RESOLVE_SHUTDOWN:
            ngx_http_upstream_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
            return NGX_YIELD;

        default:
            /* default fallback action: check next upstream */
            return NGX_DECLINED;
        }

        return NGX_DECLINED;
    }

    if (dscf->fail_check
        && (ngx_time() - dscf->fail_check < dscf->fail_timeout))
    {
        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                       "in fail timeout period, fallback: %ui", dscf->fallback);

        switch (dscf->fallback) {

        case NGX_HTTP_UPSTREAM_DYN_RESOLVE_STALE:
            return bp->original_get_peer(pc, bp->data);

        case NGX_HTTP_UPSTREAM_DYN_RESOLVE_SHUTDOWN:
            ngx_http_upstream_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
            return NGX_YIELD;

        default:
            /* default fallback action: check next upstream, still need
             * to get peer in fail timeout period
             */
            return bp->original_get_peer(pc, bp->data);
        }

        return NGX_DECLINED;
    }

    /* NGX_HTTP_UPSTREAM_DYN_RESOLVE_INIT,  ask balancer */

    rc = bp->original_get_peer(pc, bp->data);

    if (rc != NGX_OK) {
        return rc;
    }

    /* resolve name */

    if (pc->host == NULL) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                       "load balancer doesn't support dyn resolve!");
        return NGX_OK;
    }

    if (ngx_inet_addr(pc->host->data, pc->host->len) != INADDR_NONE) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, pc->log, 0,
                       "host is an IP address, connect directly!");
        return NGX_OK;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
    if (clcf->resolver == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "resolver has not been configured!");
        return NGX_OK;
    }

    temp.name = *pc->host;

    ctx = ngx_resolve_start(clcf->resolver, &temp);
    if (ctx == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "resolver start failed!");
        return NGX_OK;
    }

    if (ctx == NGX_NO_RESOLVER) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "resolver started but no resolver!");
        return NGX_OK;
    }

    ctx->name = *pc->host;
    /* TODO remove */
    // ctx->type = NGX_RESOLVE_A;
    /* END */
    ctx->handler = ngx_http_upstream_dynamic_handler;
    ctx->data = bp;
    ctx->timeout = clcf->resolver_timeout;

    u->dyn_resolve_ctx = ctx;

    if (ngx_resolve_name(ctx) != NGX_OK) {
        ngx_log_error(NGX_LOG_ERR, pc->log, 0,
                      "resolver name failed!\n");

        u->dyn_resolve_ctx = NULL;

        return NGX_OK;
    }

    return NGX_YIELD;
}