#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* ngx_msec_t ;
typedef  int ngx_int_t ;
struct TYPE_5__ {TYPE_1__* conf; void* read_timeout; void* send_timeout; void* connect_timeout; } ;
typedef  TYPE_2__ ngx_http_lua_socket_tcp_upstream_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {void* read_timeout; void* send_timeout; void* connect_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_CONNECT_TIMEOUT_INDEX ; 
 int /*<<< orphan*/  SOCKET_CTX_INDEX ; 
 int /*<<< orphan*/  SOCKET_READ_TIMEOUT_INDEX ; 
 int /*<<< orphan*/  SOCKET_SEND_TIMEOUT_INDEX ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ngx_http_lua_socket_tcp_settimeouts(lua_State *L)
{
    int                     n;
    ngx_int_t               connect_timeout, send_timeout, read_timeout;

    ngx_http_lua_socket_tcp_upstream_t  *u;

    n = lua_gettop(L);

    if (n != 4) {
        return luaL_error(L, "ngx.socket settimout: expecting 4 arguments "
                          "(including the object) but seen %d", lua_gettop(L));
    }

    connect_timeout = (ngx_int_t) lua_tonumber(L, 2);
    if (connect_timeout >> 31) {
        return luaL_error(L, "bad timeout value");
    }

    send_timeout = (ngx_int_t) lua_tonumber(L, 3);
    if (send_timeout >> 31) {
        return luaL_error(L, "bad timeout value");
    }

    read_timeout = (ngx_int_t) lua_tonumber(L, 4);
    if (read_timeout >> 31) {
        return luaL_error(L, "bad timeout value");
    }

    lua_rawseti(L, 1, SOCKET_READ_TIMEOUT_INDEX);
    lua_rawseti(L, 1, SOCKET_SEND_TIMEOUT_INDEX);
    lua_rawseti(L, 1, SOCKET_CONNECT_TIMEOUT_INDEX);

    lua_rawgeti(L, 1, SOCKET_CTX_INDEX);
    u = lua_touserdata(L, -1);

    if (u) {
        if (connect_timeout > 0) {
            u->connect_timeout = (ngx_msec_t) connect_timeout;

        } else {
            u->connect_timeout = u->conf->connect_timeout;
        }

        if (send_timeout > 0) {
            u->send_timeout = (ngx_msec_t) send_timeout;

        } else {
            u->send_timeout = u->conf->send_timeout;
        }

        if (read_timeout > 0) {
            u->read_timeout = (ngx_msec_t) read_timeout;

        } else {
            u->read_timeout = u->conf->read_timeout;
        }
    }

    return 0;
}