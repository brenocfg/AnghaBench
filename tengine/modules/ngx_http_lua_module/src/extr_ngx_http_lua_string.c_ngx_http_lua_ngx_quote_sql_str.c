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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int NGX_ERROR ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t ngx_http_lua_ngx_escape_sql_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_quote_sql_str(lua_State *L)
{
    size_t                   len, dlen, escape;
    u_char                  *p;
    u_char                  *src, *dst;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting one argument");
    }

    src = (u_char *) luaL_checklstring(L, 1, &len);

    if (len == 0) {
        dst = (u_char *) "''";
        dlen = sizeof("''") - 1;
        lua_pushlstring(L, (char *) dst, dlen);
        return 1;
    }

    escape = ngx_http_lua_ngx_escape_sql_str(NULL, src, len);

    dlen = sizeof("''") - 1 + len + escape;

    p = lua_newuserdata(L, dlen);

    dst = p;

    *p++ = '\'';

    if (escape == 0) {
        p = ngx_copy(p, src, len);

    } else {
        p = (u_char *) ngx_http_lua_ngx_escape_sql_str(p, src, len);
    }

    *p++ = '\'';

    if (p != dst + dlen) {
        return NGX_ERROR;
    }

    lua_pushlstring(L, (char *) dst, p - dst);

    return 1;
}