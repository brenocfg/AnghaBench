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
 scalar_t__ LUA_TUSERDATA ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tag ; 

__attribute__((used)) static int is_cs_data(lua_State *L, int idx) {
	if (LUA_TUSERDATA == lua_type(L, idx) && lua_getmetatable(L, idx)) {
		lua_pushlightuserdata(L, &tag);
		lua_rawget(L,-2);
		if (!lua_isnil (L,-1)) {
			lua_pop (L, 2);
			return 1;
		}
		lua_pop (L, 2);
	}
	return 0;
}