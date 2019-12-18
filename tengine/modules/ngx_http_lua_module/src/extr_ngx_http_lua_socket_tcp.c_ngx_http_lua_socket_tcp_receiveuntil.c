#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_12__ {unsigned int inclusive; } ;
typedef  TYPE_4__ ngx_http_lua_socket_compiled_pattern_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  LUA_TBOOLEAN 129 
#define  LUA_TNIL 128 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 TYPE_4__* lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_lua_socket_compile_pattern (int /*<<< orphan*/ *,scalar_t__,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_receiveuntil_iterator ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  pattern_udata_metatable_key ; 

__attribute__((used)) static int
ngx_http_lua_socket_tcp_receiveuntil(lua_State *L)
{
    ngx_http_request_t                  *r;
    int                                  n;
    ngx_str_t                            pat;
    ngx_int_t                            rc;
    size_t                               size;
    unsigned                             inclusive = 0;

    ngx_http_lua_socket_compiled_pattern_t     *cp;

    n = lua_gettop(L);
    if (n != 2 && n != 3) {
        return luaL_error(L, "expecting 2 or 3 arguments "
                          "(including the object), but got %d", n);
    }

    if (n == 3) {
        /* check out the options table */

        luaL_checktype(L, 3, LUA_TTABLE);

        lua_getfield(L, 3, "inclusive");

        switch (lua_type(L, -1)) {
            case LUA_TNIL:
                /* do nothing */
                break;

            case LUA_TBOOLEAN:
                if (lua_toboolean(L, -1)) {
                    inclusive = 1;
                }
                break;

            default:
                return luaL_error(L, "bad \"inclusive\" option value type: %s",
                                  luaL_typename(L, -1));

        }

        lua_pop(L, 2);
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request found");
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "lua tcp socket calling receiveuntil() method");

    luaL_checktype(L, 1, LUA_TTABLE);

    pat.data = (u_char *) luaL_checklstring(L, 2, &pat.len);
    if (pat.len == 0) {
        lua_pushnil(L);
        lua_pushliteral(L, "pattern is empty");
        return 2;
    }

    size = sizeof(ngx_http_lua_socket_compiled_pattern_t);

    cp = lua_newuserdata(L, size);
    if (cp == NULL) {
        return luaL_error(L, "no memory");
    }

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          pattern_udata_metatable_key));
    lua_rawget(L, LUA_REGISTRYINDEX);
    lua_setmetatable(L, -2);

    ngx_memzero(cp, size);

    cp->inclusive = inclusive;

    rc = ngx_http_lua_socket_compile_pattern(pat.data, pat.len, cp,
                                             r->connection->log);

    if (rc != NGX_OK) {
        lua_pushnil(L);
        lua_pushliteral(L, "failed to compile pattern");
        return 2;
    }

    lua_pushcclosure(L, ngx_http_lua_socket_receiveuntil_iterator, 3);
    return 1;
}