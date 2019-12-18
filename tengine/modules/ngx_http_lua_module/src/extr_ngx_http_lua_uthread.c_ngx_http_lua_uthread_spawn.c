#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_8__ {TYPE_2__* cur_co_ctx; int /*<<< orphan*/  co_op; int /*<<< orphan*/  uthreads; } ;
typedef  TYPE_1__ ngx_http_lua_ctx_t ;
struct TYPE_9__ {int is_uthread; int thread_spawn_yielded; int /*<<< orphan*/  co; struct TYPE_9__* parent_co_ctx; int /*<<< orphan*/  co_status; int /*<<< orphan*/  co_ref; } ;
typedef  TYPE_2__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_RUNNING ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_USER_THREAD_RESUME ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  coroutines_key ; 
 int /*<<< orphan*/  dd (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int lua_yield (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_coroutine_create_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__**) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 scalar_t__ ngx_http_lua_post_thread (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_lua_probe_user_thread_spawn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngx_http_lua_uthread_spawn(lua_State *L)
{
    int                           n;
    ngx_http_request_t           *r;
    ngx_http_lua_ctx_t           *ctx;
    ngx_http_lua_co_ctx_t        *coctx = NULL;

    n = lua_gettop(L);

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        return luaL_error(L, "no request ctx found");
    }

    ngx_http_lua_coroutine_create_helper(L, r, ctx, &coctx);

    /* anchor the newly created coroutine into the Lua registry */

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          coroutines_key));
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_pushvalue(L, -2);
    coctx->co_ref = luaL_ref(L, -2);
    lua_pop(L, 1);

    if (n > 1) {
        lua_replace(L, 1);
        lua_xmove(L, coctx->co, n - 1);
    }

    coctx->is_uthread = 1;
    ctx->uthreads++;

    coctx->co_status = NGX_HTTP_LUA_CO_RUNNING;
    ctx->co_op = NGX_HTTP_LUA_USER_THREAD_RESUME;

    ctx->cur_co_ctx->thread_spawn_yielded = 1;

    if (ngx_http_lua_post_thread(r, ctx, ctx->cur_co_ctx) != NGX_OK) {
        return luaL_error(L, "no memory");
    }

    coctx->parent_co_ctx = ctx->cur_co_ctx;
    ctx->cur_co_ctx = coctx;

    ngx_http_lua_probe_user_thread_spawn(r, L, coctx->co);

    dd("yielding with arg %s, top=%d, index-1:%s", luaL_typename(L, -1),
       (int) lua_gettop(L), luaL_typename(L, 1));
    return lua_yield(L, 1);
}