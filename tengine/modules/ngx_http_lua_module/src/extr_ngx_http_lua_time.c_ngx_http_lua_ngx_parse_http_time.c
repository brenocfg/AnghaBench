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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_parse_time (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_parse_http_time(lua_State *L)
{
    u_char                              *p;
    size_t                               len;
    time_t                               time;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting one argument");
    }

    p = (u_char *) luaL_checklstring(L, 1, &len);

    time = ngx_http_parse_time(p, len);
    if (time == NGX_ERROR) {
        lua_pushnil(L);
        return 1;
    }

    lua_pushnumber(L, (lua_Number) time);

    return 1;
}