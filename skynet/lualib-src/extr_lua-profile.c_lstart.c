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
 int /*<<< orphan*/  LUA_TTHREAD ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 double get_time () ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  lua_pushthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
lstart(lua_State *L) {
	if (lua_gettop(L) != 0) {
		lua_settop(L,1);
		luaL_checktype(L, 1, LUA_TTHREAD);
	} else {
		lua_pushthread(L);
	}
	lua_pushvalue(L, 1);	// push coroutine
	lua_rawget(L, lua_upvalueindex(2));
	if (!lua_isnil(L, -1)) {
		return luaL_error(L, "Thread %p start profile more than once", lua_topointer(L, 1));
	}
	lua_pushvalue(L, 1);	// push coroutine
	lua_pushnumber(L, 0);
	lua_rawset(L, lua_upvalueindex(2));

	lua_pushvalue(L, 1);	// push coroutine
	double ti = get_time();
#ifdef DEBUG_LOG
	fprintf(stderr, "PROFILE [%p] start\n", L);
#endif
	lua_pushnumber(L, ti);
	lua_rawset(L, lua_upvalueindex(1));

	return 0;
}