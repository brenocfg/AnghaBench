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
struct table {int dummy; } ;
struct ctrl {struct table* update; struct table* root; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TLIGHTUSERDATA ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  LUA_TUSERDATA ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setuservalue (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lupdate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	luaL_checktype(L, 3, LUA_TTABLE);
	struct ctrl * c= lua_touserdata(L, 1);
	struct table *n = lua_touserdata(L, 2);
	if (c->root == n) {
		return luaL_error(L, "You should update a new object");
	}
	lua_settop(L, 3);
	lua_setuservalue(L, 1);
	c->update = n;

	return 0;
}