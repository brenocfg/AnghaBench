#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_13__ {int /*<<< orphan*/  data; scalar_t__ len; } ;
struct TYPE_15__ {TYPE_2__* connection; TYPE_1__ uri; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_16__ {TYPE_5__* cur_co_ctx; } ;
typedef  TYPE_4__ ngx_http_lua_ctx_t ;
struct TYPE_18__ {int delayed; int /*<<< orphan*/  log; TYPE_5__* data; int /*<<< orphan*/  handler; } ;
struct TYPE_17__ {TYPE_6__ sleep; TYPE_3__* data; int /*<<< orphan*/  cleanup; } ;
typedef  TYPE_5__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_5__*) ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_sleep_cleanup ; 
 int /*<<< orphan*/  ngx_http_lua_sleep_handler ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_delayed_events ; 

__attribute__((used)) static int
ngx_http_lua_ngx_sleep(lua_State *L)
{
    int                          n;
    ngx_int_t                    delay; /* in msec */
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;
    ngx_http_lua_co_ctx_t       *coctx;

    n = lua_gettop(L);
    if (n != 1) {
        return luaL_error(L, "attempt to pass %d arguments, but accepted 1", n);
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    delay = (ngx_int_t) (luaL_checknumber(L, 1) * 1000);

    if (delay < 0) {
        return luaL_error(L, "invalid sleep duration \"%d\"", delay);
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                               | NGX_HTTP_LUA_CONTEXT_ACCESS
                               | NGX_HTTP_LUA_CONTEXT_CONTENT
                               | NGX_HTTP_LUA_CONTEXT_TIMER
                               | NGX_HTTP_LUA_CONTEXT_SSL_CERT
                               | NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH);

    coctx = ctx->cur_co_ctx;
    if (coctx == NULL) {
        return luaL_error(L, "no co ctx found");
    }

    ngx_http_lua_cleanup_pending_operation(coctx);
    coctx->cleanup = ngx_http_lua_sleep_cleanup;
    coctx->data = r;

    coctx->sleep.handler = ngx_http_lua_sleep_handler;
    coctx->sleep.data = coctx;
    coctx->sleep.log = r->connection->log;

    if (delay == 0) {
#ifdef HAVE_POSTED_DELAYED_EVENTS_PATCH
        dd("posting 0 sec sleep event to head of delayed queue");

        coctx->sleep.delayed = 1;
        ngx_post_event(&coctx->sleep, &ngx_posted_delayed_events);
#else
        ngx_log_error(NGX_LOG_WARN, r->connection->log, 0, "ngx.sleep(0)"
                      " called without delayed events patch, this will"
                      " hurt performance");
        ngx_add_timer(&coctx->sleep, (ngx_msec_t) delay);
#endif

    } else {
        dd("adding timer with delay %lu ms, r:%.*s", (unsigned long) delay,
           (int) r->uri.len, r->uri.data);

        ngx_add_timer(&coctx->sleep, (ngx_msec_t) delay);
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua ready to sleep for %d ms", delay);

    return lua_yield(L, 0);
}