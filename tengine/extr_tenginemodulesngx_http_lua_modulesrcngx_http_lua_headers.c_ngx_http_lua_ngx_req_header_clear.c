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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int ngx_http_lua_ngx_req_header_set_helper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_req_header_clear(lua_State *L)
{
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting one arguments, but seen %d",
                          lua_gettop(L));
    }

    lua_pushnil(L);

    return ngx_http_lua_ngx_req_header_set_helper(L);
}