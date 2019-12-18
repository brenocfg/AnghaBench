#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_3__ {scalar_t__ socket_errno; } ;
typedef  TYPE_1__ ngx_http_lua_socket_tcp_upstream_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  errstr ;

/* Variables and functions */
 int NGX_HTTP_LUA_SOCKET_FT_BUFTOOSMALL ; 
 int NGX_HTTP_LUA_SOCKET_FT_CLIENTABORT ; 
 int NGX_HTTP_LUA_SOCKET_FT_CLOSED ; 
 int NGX_HTTP_LUA_SOCKET_FT_NOMEM ; 
 int NGX_HTTP_LUA_SOCKET_FT_RESOLVER ; 
 int NGX_HTTP_LUA_SOCKET_FT_SSL ; 
 int NGX_HTTP_LUA_SOCKET_FT_TIMEOUT ; 
 int NGX_MAX_ERROR_STR ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_strerror (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_strerror_r (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ngx_http_lua_socket_prepare_error_retvals(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u, lua_State *L, ngx_uint_t ft_type)
{
    u_char           errstr[NGX_MAX_ERROR_STR];
    u_char          *p;

    if (ft_type & (NGX_HTTP_LUA_SOCKET_FT_RESOLVER
                   | NGX_HTTP_LUA_SOCKET_FT_SSL))
    {
        return 2;
    }

    lua_pushnil(L);

    if (ft_type & NGX_HTTP_LUA_SOCKET_FT_TIMEOUT) {
        lua_pushliteral(L, "timeout");

    } else if (ft_type & NGX_HTTP_LUA_SOCKET_FT_CLOSED) {
        lua_pushliteral(L, "closed");

    } else if (ft_type & NGX_HTTP_LUA_SOCKET_FT_BUFTOOSMALL) {
        lua_pushliteral(L, "buffer too small");

    } else if (ft_type & NGX_HTTP_LUA_SOCKET_FT_NOMEM) {
        lua_pushliteral(L, "no memory");

    } else if (ft_type & NGX_HTTP_LUA_SOCKET_FT_CLIENTABORT) {
        lua_pushliteral(L, "client aborted");

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