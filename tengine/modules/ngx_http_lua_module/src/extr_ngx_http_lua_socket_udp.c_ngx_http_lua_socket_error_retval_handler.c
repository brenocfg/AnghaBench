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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_8__ {int ft_type; scalar_t__ socket_errno; } ;
typedef  TYPE_3__ ngx_http_lua_socket_udp_upstream_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  errstr ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_SOCKET_FT_BUFTOOSMALL ; 
 int NGX_HTTP_LUA_SOCKET_FT_CLOSED ; 
 int NGX_HTTP_LUA_SOCKET_FT_NOMEM ; 
 int NGX_HTTP_LUA_SOCKET_FT_PARTIALWRITE ; 
 int NGX_HTTP_LUA_SOCKET_FT_RESOLVER ; 
 int NGX_HTTP_LUA_SOCKET_FT_TIMEOUT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int NGX_MAX_ERROR_STR ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ngx_strerror (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_strerror_r (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ngx_http_lua_socket_error_retval_handler(ngx_http_request_t *r,
    ngx_http_lua_socket_udp_upstream_t *u, lua_State *L)
{
    u_char           errstr[NGX_MAX_ERROR_STR];
    u_char          *p;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua udp socket error retval handler");

    if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_RESOLVER) {
        return 2;
    }

    lua_pushnil(L);

    if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_PARTIALWRITE) {
        lua_pushliteral(L, "partial write");

    } else if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_TIMEOUT) {
        lua_pushliteral(L, "timeout");

    } else if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_CLOSED) {
        lua_pushliteral(L, "closed");

    } else if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_BUFTOOSMALL) {
        lua_pushliteral(L, "buffer too small");

    } else if (u->ft_type & NGX_HTTP_LUA_SOCKET_FT_NOMEM) {
        lua_pushliteral(L, "no memory");

    } else {

        if (u->socket_errno) {
#if defined(nginx_version) && nginx_version >= 9000
            p = ngx_strerror(u->socket_errno, errstr, sizeof(errstr));
#else
            p = ngx_strerror_r(u->socket_errno, errstr, sizeof(errstr));
#endif
            /* for compatibility with LuaSocket */
            ngx_strlow(errstr, errstr, p - errstr);
            lua_pushlstring(L, (char *) errstr, p - errstr);

        } else {
            lua_pushliteral(L, "error");
        }
    }

    return 2;
}