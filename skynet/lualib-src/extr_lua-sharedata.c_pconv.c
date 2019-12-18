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
struct context {scalar_t__ string_index; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int LUA_OK ; 
 int /*<<< orphan*/  convtable ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct context*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pconv(lua_State *L) {
	struct context *ctx = lua_touserdata(L,1);
	lua_State * pL = lua_touserdata(L, 2);
	int ret;

	lua_settop(L, 0);

	// init L (may throw memory error)
	// create a table for string map
	lua_newtable(L);

	lua_pushcfunction(pL, convtable);
	lua_pushvalue(pL,1);
	lua_pushlightuserdata(pL, ctx);

	ret = lua_pcall(pL, 2, 0, 0);
	if (ret != LUA_OK) {
		size_t sz = 0;
		const char * error = lua_tolstring(pL, -1, &sz);
		lua_pushlstring(L, error, sz);
		lua_error(L);
		// never get here
	}

	luaL_checkstack(L, ctx->string_index + 3, NULL);
	lua_settop(L,1);

	return 1;
}