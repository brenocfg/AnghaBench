#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_close ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_receive ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_send ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_setpeername ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_settimeout ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_upstream_destroy ; 
 int /*<<< orphan*/  socket_udp_metatable_key ; 
 int /*<<< orphan*/  udp_udata_metatable_key ; 

void
ngx_http_lua_inject_socket_udp_api(ngx_log_t *log, lua_State *L)
{
    lua_getfield(L, -1, "socket"); /* ngx socket */

    lua_pushcfunction(L, ngx_http_lua_socket_udp);
    lua_setfield(L, -2, "udp"); /* ngx socket */

    /* udp socket object metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          socket_udp_metatable_key));
    lua_createtable(L, 0 /* narr */, 6 /* nrec */);

    lua_pushcfunction(L, ngx_http_lua_socket_udp_setpeername);
    lua_setfield(L, -2, "setpeername"); /* ngx socket mt */

    lua_pushcfunction(L, ngx_http_lua_socket_udp_send);
    lua_setfield(L, -2, "send");

    lua_pushcfunction(L, ngx_http_lua_socket_udp_receive);
    lua_setfield(L, -2, "receive");

    lua_pushcfunction(L, ngx_http_lua_socket_udp_settimeout);
    lua_setfield(L, -2, "settimeout"); /* ngx socket mt */

    lua_pushcfunction(L, ngx_http_lua_socket_udp_close);
    lua_setfield(L, -2, "close"); /* ngx socket mt */

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

    /* udp socket object metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          udp_udata_metatable_key));
    lua_createtable(L, 0 /* narr */, 1 /* nrec */); /* metatable */
    lua_pushcfunction(L, ngx_http_lua_socket_udp_upstream_destroy);
    lua_setfield(L, -2, "__gc");
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

    lua_pop(L, 1);
}