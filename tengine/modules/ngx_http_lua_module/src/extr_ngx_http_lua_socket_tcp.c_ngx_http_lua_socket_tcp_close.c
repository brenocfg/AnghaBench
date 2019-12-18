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
struct TYPE_8__ {int /*<<< orphan*/ * connection; } ;
struct TYPE_9__ {scalar_t__ body_downstream; scalar_t__ raw_downstream; int /*<<< orphan*/ * request; scalar_t__ write_closed; scalar_t__ read_closed; TYPE_1__ peer; } ;
typedef  TYPE_2__ ngx_http_lua_socket_tcp_upstream_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  SOCKET_CTX_INDEX ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_check_busy_connecting (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_check_busy_reading (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_check_busy_writing (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_finalize (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
ngx_http_lua_socket_tcp_close(lua_State *L)
{
    ngx_http_request_t                  *r;
    ngx_http_lua_socket_tcp_upstream_t  *u;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting 1 argument "
                          "(including the object) but seen %d", lua_gettop(L));
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    luaL_checktype(L, 1, LUA_TTABLE);

    lua_rawgeti(L, 1, SOCKET_CTX_INDEX);
    u = lua_touserdata(L, -1);
    lua_pop(L, 1);

    if (u == NULL
        || u->peer.connection == NULL
        || (u->read_closed && u->write_closed))
    {
        lua_pushnil(L);
        lua_pushliteral(L, "closed");
        return 2;
    }

    if (u->request != r) {
        return luaL_error(L, "bad request");
    }

    ngx_http_lua_socket_check_busy_connecting(r, u, L);
    ngx_http_lua_socket_check_busy_reading(r, u, L);
    ngx_http_lua_socket_check_busy_writing(r, u, L);

    if (u->raw_downstream || u->body_downstream) {
        lua_pushnil(L);
        lua_pushliteral(L, "attempt to close a request socket");
        return 2;
    }

    ngx_http_lua_socket_tcp_finalize(r, u);

    lua_pushinteger(L, 1);
    return 1;
}