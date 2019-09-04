#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_ctx_t ;
struct TYPE_9__ {scalar_t__ co_ref; int /*<<< orphan*/  co_status; int /*<<< orphan*/  co; } ;
typedef  TYPE_3__ ngx_http_lua_co_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_CO_DEAD ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  coroutines_key ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_probe_thread_delete (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
ngx_http_lua_del_thread(ngx_http_request_t *r, lua_State *L,
    ngx_http_lua_ctx_t *ctx, ngx_http_lua_co_ctx_t *coctx)
{
    if (coctx->co_ref == LUA_NOREF) {
        return;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua deleting light thread");

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          coroutines_key));
    lua_rawget(L, LUA_REGISTRYINDEX);

    ngx_http_lua_probe_thread_delete(r, coctx->co, ctx);

    luaL_unref(L, -1, coctx->co_ref);
    coctx->co_ref = LUA_NOREF;
    coctx->co_status = NGX_HTTP_LUA_CO_DEAD;

    lua_pop(L, 1);
}