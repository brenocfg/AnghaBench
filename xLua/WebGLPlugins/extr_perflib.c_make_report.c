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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 scalar_t__ LUA_TLIGHTUSERDATA ; 
 int ROOT_TABLE ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  luaL_addstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_touserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void make_report(lua_State* L, lua_State* dL) {
	int size = 0;
	int i = 0;
	luaL_Buffer b;
	
	lua_newtable(L);
	
	lua_pushnil(dL);
	while (lua_next(dL, ROOT_TABLE) != 0) {
		lua_getfield(dL, -1, "name");
		if (lua_isnil(dL, -1)) {
			lua_pop(dL, 2);
			continue;
		} else {
			lua_pop(dL, 1);
		}
		
		lua_newtable(L);
		size = 0;
		
		lua_pushnil(dL);
		while (lua_next(dL, -2) != 0) {
			if (LUA_TLIGHTUSERDATA == lua_type(dL, -2)) { 
				size += (int)lua_tointeger(dL, -1);
			} 
			
			lua_pop(dL, 1);
		}
		lua_pushnumber(L, size);
		lua_setfield(L, -2, "size");
		
		lua_pushfstring(L, "%p", lua_touserdata(dL, -2));
		lua_setfield(L, -2, "pointer");
		
		lua_getfield(dL, -1, "name");
		lua_pushstring(L, lua_tostring(dL, -1));
		lua_pop(dL, 1);
		lua_setfield(L, -2, "name");
		
		lua_getfield(dL, -1, "type");
		lua_pushnumber(L, lua_tonumber(dL, -1));
		lua_pop(dL, 1);
		lua_setfield(L, -2, "type");
		
		lua_getfield(dL, -1, "used_in");
		luaL_buffinit(L, &b);
		lua_pushnil(dL);
		while (lua_next(dL, -2) != 0) {
			lua_pop(dL, 1);
			luaL_addstring(&b, lua_tostring(dL, -1));
			luaL_addchar(&b, ';');
		}
		luaL_pushresult(&b);
		lua_pop(dL, 1);
		lua_setfield(L, -2, "used_in");
		
		++i;
		lua_rawseti(L, -2, i);
		
		lua_pop(dL, 1);
	}
}