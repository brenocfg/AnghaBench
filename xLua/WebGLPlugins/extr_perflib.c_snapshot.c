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
 int /*<<< orphan*/  LUA_GLOBALSINDEX ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  LUA_RIDX_GLOBALS ; 
 int RT_GLOBAL ; 
 int RT_REGISTRY ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,void const*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 void* lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  make_report (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mark_root_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int snapshot(lua_State* L) {
	lua_State *dL = luaL_newstate();
	int len;
	const void * p;
	lua_newtable(dL);
	
#if LUA_VERSION_NUM == 503
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
#else
	lua_pushvalue(L, LUA_GLOBALSINDEX);
#endif
	mark_root_table(L, dL, RT_GLOBAL);
	lua_pop(L, 1);
	
	lua_pushvalue(L, LUA_REGISTRYINDEX);
	p = lua_topointer(L, -1);
	len = mark_root_table(L, dL, RT_REGISTRY);
	lua_pop(L, 1);
	
	make_report(L, dL);
	
	lua_newtable(L);
	lua_pushstring(L, "[REGISTRY Level 1]");
	lua_setfield(L, -2, "name");
	lua_pushnumber(L, RT_REGISTRY);
	lua_setfield(L, -2, "type");
	lua_pushnumber(L, len);
	lua_setfield(L, -2, "size");
	lua_pushfstring(L, "%p", p);
	lua_setfield(L, -2, "pointer");
	lua_pushstring(L, "");
	lua_setfield(L, -2, "used_in");
	lua_rawseti(L, -2, lua_objlen(L, -2) + 1);
	
	lua_close(dL);
	
	return 1;
}