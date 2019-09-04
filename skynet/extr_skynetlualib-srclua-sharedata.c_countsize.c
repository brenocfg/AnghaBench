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
typedef  int lua_Integer ;

/* Variables and functions */
 int LUA_TNUMBER ; 
 int LUA_TSTRING ; 
 int LUA_TTABLE ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
countsize(lua_State *L, int sizearray) {
	int n = 0;
	lua_pushnil(L);
	while (lua_next(L, 1) != 0) {
		int type = lua_type(L, -2);
		++n;
		if (type == LUA_TNUMBER) {
			if (!lua_isinteger(L, -2)) {
				luaL_error(L, "Invalid key %f", lua_tonumber(L, -2));
			}
			lua_Integer nkey = lua_tointeger(L, -2);
			if (nkey > 0 && nkey <= sizearray) {
				--n;
			}
		} else if (type != LUA_TSTRING && type != LUA_TTABLE) {
			luaL_error(L, "Invalid key type %s", lua_typename(L, type));
		}
		lua_pop(L, 1);
	}

	return n;
}