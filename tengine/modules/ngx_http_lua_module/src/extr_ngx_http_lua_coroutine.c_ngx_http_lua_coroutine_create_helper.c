#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
struct TYPE_6__ {int co_top; int /*<<< orphan*/  co_status; int /*<<< orphan*/ * co; int /*<<< orphan*/  co_ref; } ;
typedef  TYPE_1__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 int NGX_HTTP_LUA_CONTEXT_ACCESS ; 
 int NGX_HTTP_LUA_CONTEXT_CONTENT ; 
 int NGX_HTTP_LUA_CONTEXT_REWRITE ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_CERT ; 
 int NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH ; 
 int NGX_HTTP_LUA_CONTEXT_TIMER ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_SUSPENDED ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_iscfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_newthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_check_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ngx_http_lua_create_co_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ngx_http_lua_get_co_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_get_globals_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_lua_vm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_probe_user_coroutine_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_set_globals_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_set_req (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_1__*,int) ; 

int
ngx_http_lua_coroutine_create_helper(lua_State *L, ngx_http_request_t *r,
    ngx_http_lua_ctx_t *ctx, ngx_http_lua_co_ctx_t **pcoctx)
{
    lua_State                     *vm;  /* the Lua VM */
    lua_State                     *co;  /* new coroutine to be created */
    ngx_http_lua_co_ctx_t         *coctx; /* co ctx for the new coroutine */

    luaL_argcheck(L, lua_isfunction(L, 1) && !lua_iscfunction(L, 1), 1,
                  "Lua function expected");

    ngx_http_lua_check_context(L, ctx, NGX_HTTP_LUA_CONTEXT_REWRITE
                               | NGX_HTTP_LUA_CONTEXT_ACCESS
                               | NGX_HTTP_LUA_CONTEXT_CONTENT
                               | NGX_HTTP_LUA_CONTEXT_TIMER
                               | NGX_HTTP_LUA_CONTEXT_SSL_CERT
                               | NGX_HTTP_LUA_CONTEXT_SSL_SESS_FETCH);

    vm = ngx_http_lua_get_lua_vm(r, ctx);

    /* create new coroutine on root Lua state, so it always yields
     * to main Lua thread
     */
    co = lua_newthread(vm);

    ngx_http_lua_probe_user_coroutine_create(r, L, co);

    coctx = ngx_http_lua_get_co_ctx(co, ctx);
    if (coctx == NULL) {
        coctx = ngx_http_lua_create_co_ctx(r, ctx);
        if (coctx == NULL) {
            return luaL_error(L, "no memory");
        }

    } else {
        ngx_memzero(coctx, sizeof(ngx_http_lua_co_ctx_t));
        coctx->co_ref = LUA_NOREF;
    }

    coctx->co = co;
    coctx->co_status = NGX_HTTP_LUA_CO_SUSPENDED;

#ifdef OPENRESTY_LUAJIT
    ngx_http_lua_set_req(co, r);
#else
    /* make new coroutine share globals of the parent coroutine.
     * NOTE: globals don't have to be separated! */
    ngx_http_lua_get_globals_table(L);
    lua_xmove(L, co, 1);
    ngx_http_lua_set_globals_table(co);
#endif

    lua_xmove(vm, L, 1);    /* move coroutine from main thread to L */

    lua_pushvalue(L, 1);    /* copy entry function to top of L*/
    lua_xmove(L, co, 1);    /* move entry function from L to co */

    if (pcoctx) {
        *pcoctx = coctx;
    }

#ifdef NGX_LUA_USE_ASSERT
    coctx->co_top = 1;
#endif

    return 1;    /* return new coroutine to Lua */
}