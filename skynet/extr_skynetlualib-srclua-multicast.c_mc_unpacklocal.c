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
struct mc_package {scalar_t__ size; struct mc_package* data; } ;
typedef  int /*<<< orphan*/  pack ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct mc_package*) ; 
 struct mc_package** lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mc_unpacklocal(lua_State *L) {
	struct mc_package ** pack = lua_touserdata(L,1);
	int sz = luaL_checkinteger(L,2);
	if (sz != sizeof(pack)) {
		return luaL_error(L, "Invalid multicast package size %d", sz);
	}
	lua_pushlightuserdata(L, *pack);
	lua_pushlightuserdata(L, (*pack)->data);
	lua_pushinteger(L, (lua_Integer)((*pack)->size));
	return 3;
}