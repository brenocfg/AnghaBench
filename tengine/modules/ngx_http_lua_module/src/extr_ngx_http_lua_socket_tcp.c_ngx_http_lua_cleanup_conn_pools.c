#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ ngx_http_lua_socket_pool_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_shutdown_pool_helper (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_pool_key ; 

void
ngx_http_lua_cleanup_conn_pools(lua_State *L)
{
    ngx_http_lua_socket_pool_t          *spool;

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          socket_pool_key));
    lua_rawget(L, LUA_REGISTRYINDEX); /* table */

    lua_pushnil(L);  /* first key */
    while (lua_next(L, -2) != 0) {
        /* tb key val */
        spool = lua_touserdata(L, -1);

        if (spool != NULL) {
            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                           "lua tcp socket keepalive: free connection pool %p "
                           "for \"%s\"", spool, spool->key);

            ngx_http_lua_socket_shutdown_pool_helper(spool);
        }

        lua_pop(L, 1);
    }

    lua_pop(L, 1);
}