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
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  LUA_TLIGHTUSERDATA ; 
 int /*<<< orphan*/  TABLES ; 
 int /*<<< orphan*/  create_proxy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawsetp (int /*<<< orphan*/ *,int,char const*) ; 
 char* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lnew(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	const char * data = lua_touserdata(L, 1);
	// hold ref to data
	lua_getfield(L, LUA_REGISTRYINDEX, TABLES);
	lua_pushvalue(L, 1);
	lua_rawsetp(L, -2, data);

	create_proxy(L, data, 0);
	return 1;
}