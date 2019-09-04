#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
struct TYPE_16__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_17__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_15__ {int /*<<< orphan*/ * connection; } ;
struct TYPE_18__ {int ft_type; int /*<<< orphan*/  socket_errno; TYPE_2__ udp_connection; scalar_t__ waiting; TYPE_4__* request; } ;
typedef  TYPE_5__ ngx_http_lua_socket_udp_upstream_t ;
struct TYPE_19__ {scalar_t__ log_socket_errors; } ;
typedef  TYPE_6__ ngx_http_lua_loc_conf_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
#define  LUA_TBOOLEAN 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_LUA_SOCKET_FT_PARTIALWRITE ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  SOCKET_CTX_INDEX ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 TYPE_5__* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 size_t ngx_http_lua_calc_strlen_in_table (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  ngx_http_lua_copy_str_in_table (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_4__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int ngx_http_lua_socket_error_retval_handler (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ngx_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 

__attribute__((used)) static int
ngx_http_lua_socket_udp_send(lua_State *L)
{
    ssize_t                              n;
    ngx_http_request_t                  *r;
    u_char                              *p;
    size_t                               len;
    ngx_http_lua_socket_udp_upstream_t  *u;
    int                                  type;
    const char                          *msg;
    ngx_str_t                            query;
    ngx_http_lua_loc_conf_t             *llcf;

    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting 2 arguments (including the object), "
                          "but got %d", lua_gettop(L));
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "request object not found");
    }

    luaL_checktype(L, 1, LUA_TTABLE);

    lua_rawgeti(L, 1, SOCKET_CTX_INDEX);
    u = lua_touserdata(L, -1);
    lua_pop(L, 1);

    if (u == NULL || u->udp_connection.connection == NULL) {
        llcf = ngx_http_get_module_loc_conf(r, ngx_http_lua_module);

        if (llcf->log_socket_errors) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "attempt to send data on a closed socket: u:%p, c:%p",
                          u, u ? u->udp_connection.connection : NULL);
        }

        lua_pushnil(L);
        lua_pushliteral(L, "closed");
        return 2;
    }

    if (u->request != r) {
        return luaL_error(L, "bad request");
    }

    if (u->ft_type) {
        u->ft_type = 0;
    }

    if (u->waiting) {
        lua_pushnil(L);
        lua_pushliteral(L, "socket busy");
        return 2;
    }

    type = lua_type(L, 2);
    switch (type) {
        case LUA_TNUMBER:
        case LUA_TSTRING:
            lua_tolstring(L, 2, &len);
            break;

        case LUA_TTABLE:
            len = ngx_http_lua_calc_strlen_in_table(L, 2, 2, 1 /* strict */);
            break;

        case LUA_TNIL:
            len = sizeof("nil") - 1;
            break;

        case LUA_TBOOLEAN:
            if (lua_toboolean(L, 2)) {
                len = sizeof("true") - 1;

            } else {
                len = sizeof("false") - 1;
            }

            break;

        default:
            msg = lua_pushfstring(L, "string, number, boolean, nil, "
                                  "or array table expected, got %s",
                                  lua_typename(L, type));

            return luaL_argerror(L, 2, msg);
    }

    query.data = lua_newuserdata(L, len);
    query.len = len;

    switch (type) {
        case LUA_TNUMBER:
        case LUA_TSTRING:
            p = (u_char *) lua_tolstring(L, 2, &len);
            ngx_memcpy(query.data, (u_char *) p, len);
            break;

        case LUA_TTABLE:
            (void) ngx_http_lua_copy_str_in_table(L, 2, query.data);
            break;

        case LUA_TNIL:
            p = query.data;
            *p++ = 'n';
            *p++ = 'i';
            *p++ = 'l';
            break;

        case LUA_TBOOLEAN:
            p = query.data;

            if (lua_toboolean(L, 2)) {
                *p++ = 't';
                *p++ = 'r';
                *p++ = 'u';
                *p++ = 'e';

            } else {
                *p++ = 'f';
                *p++ = 'a';
                *p++ = 'l';
                *p++ = 's';
                *p++ = 'e';
            }

            break;

        default:
            return luaL_error(L, "impossible to reach here");
    }

    u->ft_type = 0;

    /* mimic ngx_http_upstream_init_request here */

#if 1
    u->waiting = 0;
#endif

    dd("sending query %.*s", (int) query.len, query.data);

    n = ngx_send(u->udp_connection.connection, query.data, query.len);

    dd("ngx_send returns %d (query len %d)", (int) n, (int) query.len);

    if (n == NGX_ERROR || n == NGX_AGAIN) {
        u->socket_errno = ngx_socket_errno;

        return ngx_http_lua_socket_error_retval_handler(r, u, L);
    }

    if (n != (ssize_t) query.len) {
        dd("not the while query was sent");

        u->ft_type |= NGX_HTTP_LUA_SOCKET_FT_PARTIALWRITE;
        return ngx_http_lua_socket_error_retval_handler(r, u, L);
    }

    dd("n == len");

    lua_pushinteger(L, 1);
    return 1;
}