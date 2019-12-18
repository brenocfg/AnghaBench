#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {scalar_t__ filter_finalize; int /*<<< orphan*/  args; int /*<<< orphan*/  uri; TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_16__ {TYPE_12__* cur_co_ctx; } ;
typedef  TYPE_3__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;
struct TYPE_13__ {int /*<<< orphan*/  co_status; int /*<<< orphan*/  co; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_DEAD ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_pending_operation (TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_http_lua_init_ctx (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_probe_coroutine_done (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_http_lua_request_cleanup (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_handle_rewrite_jump(lua_State *L, ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx)
{
    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua thread aborting request with URI rewrite jump: "
                   "\"%V?%V\"", &r->uri, &r->args);

    ngx_http_lua_cleanup_pending_operation(ctx->cur_co_ctx);

    ngx_http_lua_probe_coroutine_done(r, ctx->cur_co_ctx->co, 1);

    ctx->cur_co_ctx->co_status = NGX_HTTP_LUA_CO_DEAD;

    if (r->filter_finalize) {
        ngx_http_set_ctx(r, ctx, ngx_http_lua_module);
    }

    ngx_http_lua_request_cleanup(ctx, 1 /* forcible */);
    ngx_http_lua_init_ctx(r, ctx);

    return NGX_OK;
}