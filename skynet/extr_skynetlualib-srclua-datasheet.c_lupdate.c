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
struct proxy {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  LUA_TLIGHTUSERDATA ; 
 scalar_t__ LUA_TUSERDATA ; 
 int /*<<< orphan*/  PROXYCACHE ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_topointer (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  update_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
lupdate(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, PROXYCACHE);
	lua_pushvalue(L, 1);
	// PROXYCACHE, table
	if (lua_rawget(L, -2) != LUA_TUSERDATA) {
		luaL_error(L, "Invalid proxy table %p", lua_topointer(L, 1));
	}
	struct proxy * p = lua_touserdata(L, -1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const char * newdata = lua_touserdata(L, 2);
	update_cache(L, p->data, newdata);
	return 1;
}