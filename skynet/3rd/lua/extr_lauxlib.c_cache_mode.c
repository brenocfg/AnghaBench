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
 int CACHE_ON ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int LUA_TNUMBER ; 
 int /*<<< orphan*/  cache_key ; 
 int luaL_checkoption (int /*<<< orphan*/ *,int,char*,char const**) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int lua_rawgetp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawsetp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cache_mode(lua_State *L) {
	static const char * lst[] = {
		"OFF",
		"EXIST",
		"ON",
		NULL,
	};
	if (lua_isnoneornil(L,1)) {
		int t = lua_rawgetp(L, LUA_REGISTRYINDEX, &cache_key);
		int r = lua_tointeger(L, -1);
		if (t == LUA_TNUMBER) {
			if (r < 0  || r >= CACHE_ON) {
				r = CACHE_ON;
			}
		} else {
			r = CACHE_ON;
		}
		lua_pushstring(L, lst[r]);
		return 1;
	}
	int t = luaL_checkoption(L, 1, "OFF" , lst);
	lua_pushinteger(L, t);
	lua_rawsetp(L, LUA_REGISTRYINDEX, &cache_key);
	return 0;
}