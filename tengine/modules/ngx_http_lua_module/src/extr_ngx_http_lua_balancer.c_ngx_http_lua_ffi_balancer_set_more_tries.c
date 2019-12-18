#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_14__ {scalar_t__ tries; } ;
struct TYPE_15__ {TYPE_2__ peer; TYPE_1__* conf; } ;
typedef  TYPE_3__ ngx_http_upstream_t ;
struct TYPE_16__ {TYPE_3__* upstream; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_17__ {TYPE_7__* balancer_peer_data; } ;
typedef  TYPE_5__ ngx_http_lua_main_conf_t ;
struct TYPE_18__ {int context; } ;
typedef  TYPE_6__ ngx_http_lua_ctx_t ;
struct TYPE_19__ {scalar_t__ total_tries; int more_tries; } ;
typedef  TYPE_7__ ngx_http_lua_balancer_peer_data_t ;
struct TYPE_13__ {scalar_t__ next_upstream_tries; } ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_HTTP_LUA_CONTEXT_BALANCER ; 
 int NGX_OK ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_main_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

int
ngx_http_lua_ffi_balancer_set_more_tries(ngx_http_request_t *r,
    int count, char **err)
{
#if (nginx_version >= 1007005)
    ngx_uint_t             max_tries, total;
#endif
    ngx_http_lua_ctx_t    *ctx;
    ngx_http_upstream_t   *u;

    ngx_http_lua_main_conf_t           *lmcf;
    ngx_http_lua_balancer_peer_data_t  *bp;

    if (r == NULL) {
        *err = "no request found";
        return NGX_ERROR;
    }

    u = r->upstream;

    if (u == NULL) {
        *err = "no upstream found";
        return NGX_ERROR;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        *err = "no ctx found";
        return NGX_ERROR;
    }

    if ((ctx->context & NGX_HTTP_LUA_CONTEXT_BALANCER) == 0) {
        *err = "API disabled in the current context";
        return NGX_ERROR;
    }

    lmcf = ngx_http_get_module_main_conf(r, ngx_http_lua_module);

    bp = lmcf->balancer_peer_data;
    if (bp == NULL) {
        *err = "no upstream peer data found";
        return NGX_ERROR;
    }

#if (nginx_version >= 1007005)
    max_tries = r->upstream->conf->next_upstream_tries;
    total = bp->total_tries + r->upstream->peer.tries - 1;

    if (max_tries && total + count > max_tries) {
        count = max_tries - total;
        *err = "reduced tries due to limit";

    } else {
        *err = NULL;
    }
#else
    *err = NULL;
#endif

    bp->more_tries = count;
    return NGX_OK;
}