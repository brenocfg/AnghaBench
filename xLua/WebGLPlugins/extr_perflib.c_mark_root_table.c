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
 scalar_t__ LUA_TTABLE ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_topointer (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  make_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mark_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mark_root_table(lua_State* L, lua_State* dL, int type) {
	int len = 0;
	
	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		++len;
		if (LUA_TTABLE == lua_type(L, -1)) {
			lua_pushvalue(L, -2);
			
			make_root(dL, lua_topointer(L, -2), lua_tostring(L, -1), type, NULL, 1);
			lua_pop(L, 1);
			mark_table(L, dL);
			lua_pop(dL, 1);
		} else {
		    make_root(dL, lua_topointer(L, -1), "FUNCTION", type, NULL, 0);
			mark_object(L, dL);
			lua_pop(dL, 1);
		}
		lua_pop(L, 1);
		
		make_root(dL, lua_topointer(L, -1), "[KEY]", type, NULL, LUA_TTABLE == lua_type(L, -1));
		mark_object(L, dL);
		lua_pop(dL, 1);
	}
	
	return len;
}