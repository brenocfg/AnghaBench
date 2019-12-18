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
#define  LUA_TBOOLEAN 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 

void script_copy_value(lua_State *src, lua_State *dst, int index) {
    switch (lua_type(src, index)) {
        case LUA_TBOOLEAN:
            lua_pushboolean(dst, lua_toboolean(src, index));
            break;
        case LUA_TNIL:
            lua_pushnil(dst);
            break;
        case LUA_TNUMBER:
            lua_pushnumber(dst, lua_tonumber(src, index));
            break;
        case LUA_TSTRING:
            lua_pushstring(dst, lua_tostring(src, index));
            break;
        case LUA_TTABLE:
            lua_newtable(dst);
            lua_pushnil(src);
            while (lua_next(src, index - 1)) {
                script_copy_value(src, dst, -2);
                script_copy_value(src, dst, -1);
                lua_settable(dst, -3);
                lua_pop(src, 1);
            }
            lua_pop(src, 1);
            break;
        default:
            luaL_error(src, "cannot transfer '%s' to thread", luaL_typename(src, index));
    }
}