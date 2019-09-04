#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_7__ {int /*<<< orphan*/  co_op; TYPE_3__* cur_co_ctx; } ;
typedef  TYPE_2__ ngx_http_lua_ctx_t ;
struct TYPE_8__ {TYPE_1__* parent_co_ctx; int /*<<< orphan*/  is_uthread; int /*<<< orphan*/  co_status; } ;
typedef  TYPE_3__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/ * co; int /*<<< orphan*/  co_status; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_RUNNING ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_SUSPENDED ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_USER_CORO_YIELD ; 
 int /*<<< orphan*/  dd (char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_probe_user_coroutine_yield (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_coroutine_yield(lua_State *L)
{
    ngx_http_request_t          *r;
    ngx_http_lua_ctx_t          *ctx;
    ngx_http_lua_co_ctx_t       *coctx;

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
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

    coctx->co_status = NGX_HTTP_LUA_CO_SUSPENDED;

    ctx->co_op = NGX_HTTP_LUA_USER_CORO_YIELD;

    if (!coctx->is_uthread && coctx->parent_co_ctx) {
        dd("set coroutine to running");
        coctx->parent_co_ctx->co_status = NGX_HTTP_LUA_CO_RUNNING;

        ngx_http_lua_probe_user_coroutine_yield(r, coctx->parent_co_ctx->co, L);

    } else {
        ngx_http_lua_probe_user_coroutine_yield(r, NULL, L);
    }

    /* yield and pass retvals to main thread,
     * and resume parent coroutine there */
    return lua_yield(L, lua_gettop(L));
}