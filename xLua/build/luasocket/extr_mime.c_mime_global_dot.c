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
typedef  int lua_Number ;
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 size_t dot (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 char* luaL_optlstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mime_global_dot(lua_State *L)
{
    size_t isize = 0, state = (size_t) luaL_checknumber(L, 1);
    const char *input = luaL_optlstring(L, 2, NULL, &isize);
    const char *last = input + isize;
    luaL_Buffer buffer;
    /* end-of-input blackhole */
    if (!input) {
        lua_pushnil(L);
        lua_pushnumber(L, 2);
        return 2;
    }
    /* process all input */
    luaL_buffinit(L, &buffer);
    while (input < last) 
        state = dot(*input++, state, &buffer);
    luaL_pushresult(&buffer);
    lua_pushnumber(L, (lua_Number) state);
    return 2;
}