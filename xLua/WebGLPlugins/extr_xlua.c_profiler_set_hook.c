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
 int LUA_MASKCALL ; 
 int LUA_MASKRET ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/  hook ; 
 int /*<<< orphan*/  hook_index ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_sethook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int profiler_set_hook(lua_State *L) {
	if (lua_isnoneornil(L, 1)) {
		lua_pushlightuserdata(L, &hook_index);
		lua_pushnil(L);
		lua_rawset(L, LUA_REGISTRYINDEX);
			
		lua_sethook(L, 0, 0, 0);
	} else {
		luaL_checktype(L, 1, LUA_TFUNCTION);
		lua_pushlightuserdata(L, &hook_index);
		lua_pushvalue(L, 1);
		lua_rawset(L, LUA_REGISTRYINDEX);
		lua_sethook(L, hook, LUA_MASKCALL | LUA_MASKRET, 0);
	}
	return 0;
}