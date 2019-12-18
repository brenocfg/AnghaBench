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
 int /*<<< orphan*/  LUA_TTABLE ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_seti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skynet_free (void*) ; 

__attribute__((used)) static int
lappend(lua_State *L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	int n = lua_rawlen(L, 1);
	if (lua_isnil(L, 2)) {
		lua_settop(L, 3);
		lua_seti(L, 1, n + 1);
		return 0;
	}
	void * buffer = lua_touserdata(L, 2);
	if (buffer == NULL)
		return luaL_error(L, "Need lightuserdata");
	int sz = luaL_checkinteger(L, 3);
	lua_pushlstring(L, (const char *)buffer, sz);
	skynet_free((void *)buffer);
	lua_seti(L, 1, n+1);
	return 0;
}