#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_13__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_14__ {int /*<<< orphan*/  running_timers; } ;
typedef  TYPE_3__ ngx_http_lua_main_conf_t ;
struct TYPE_15__ {scalar_t__ context; int /*<<< orphan*/ ** cleanup; TYPE_2__* request; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {scalar_t__ fd; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_LUA_CONTEXT_TIMER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  dd (char*) ; 
 TYPE_3__* ngx_http_get_module_main_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_finalize_threads (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_lua_vm (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

void
ngx_http_lua_request_cleanup(ngx_http_lua_ctx_t *ctx, int forcible)
{
    lua_State                   *L;
    ngx_http_request_t          *r;
    ngx_http_lua_main_conf_t    *lmcf;

    /*  force coroutine handling the request quit */
    if (ctx == NULL) {
        dd("ctx is NULL");
        return;
    }

    r = ctx->request;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua request cleanup: forcible=%d", forcible);

    if (ctx->cleanup) {
        *ctx->cleanup = NULL;
        ctx->cleanup = NULL;
    }

    lmcf = ngx_http_get_module_main_conf(r, ngx_http_lua_module);

#if 1
    if (r->connection->fd == (ngx_socket_t) -1) {
        /* being a fake request */

        if (ctx->context == NGX_HTTP_LUA_CONTEXT_TIMER) {
            /* being a timer handler */
            lmcf->running_timers--;
        }
    }
#endif

    L = ngx_http_lua_get_lua_vm(r, ctx);

    ngx_http_lua_finalize_threads(r, ctx, L);
}