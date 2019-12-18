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
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  bson_create (struct bson*) ; 
 int /*<<< orphan*/  bson_destroy (struct bson*) ; 
 int /*<<< orphan*/  bson_meta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_bson ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_error (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct bson*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lencode(lua_State *L) {
	struct bson b;
	lua_settop(L,1);
	luaL_checktype(L, 1, LUA_TTABLE);
	bson_create(&b);
	lua_pushcfunction(L, encode_bson);
	lua_pushvalue(L, 1);
	lua_pushlightuserdata(L, &b);
	if (lua_pcall(L, 2, 1, 0) != LUA_OK) {
		bson_destroy(&b);
		return lua_error(L);
	}
	bson_destroy(&b);
	bson_meta(L);
	return 1;
}