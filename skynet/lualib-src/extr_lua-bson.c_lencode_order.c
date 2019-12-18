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
struct bson {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_OK ; 
 int /*<<< orphan*/  bson_create (struct bson*) ; 
 int /*<<< orphan*/  bson_destroy (struct bson*) ; 
 int /*<<< orphan*/  bson_meta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_bson_byorder ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_error (int /*<<< orphan*/ *) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct bson*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lencode_order(lua_State *L) {
	struct bson b;
	int n = lua_gettop(L);
	if (n%2 != 0) {
		return luaL_error(L, "Invalid ordered dict");
	}
	bson_create(&b);
	lua_pushvalue(L, 1);	// copy the first arg to n
	lua_pushcfunction(L, encode_bson_byorder);
	lua_replace(L, 1);
	lua_pushlightuserdata(L, &b);
	if (lua_pcall(L, n+1, 1, 0) != LUA_OK) {
		bson_destroy(&b);
		return lua_error(L);
	}
	bson_destroy(&b);
	bson_meta(L);
	return 1;
}