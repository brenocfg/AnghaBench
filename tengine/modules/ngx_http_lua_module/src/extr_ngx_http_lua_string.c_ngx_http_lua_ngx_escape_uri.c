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
 int /*<<< orphan*/  NGX_ESCAPE_URI_COMPONENT ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int ngx_http_lua_escape_uri (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_escape_uri(lua_State *L)
{
    size_t                   len, dlen;
    uintptr_t                escape;
    u_char                  *src, *dst;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting one argument");
    }

    if (lua_isnil(L, 1)) {
        lua_pushliteral(L, "");
        return 1;
    }

    src = (u_char *) luaL_checklstring(L, 1, &len);

    if (len == 0) {
        return 1;
    }

    escape = 2 * ngx_http_lua_escape_uri(NULL, src, len,
                                         NGX_ESCAPE_URI_COMPONENT);

    if (escape) {
        dlen = escape + len;
        dst = lua_newuserdata(L, dlen);
        ngx_http_lua_escape_uri(dst, src, len, NGX_ESCAPE_URI_COMPONENT);
        lua_pushlstring(L, (char *) dst, dlen);
    }

    return 1;
}