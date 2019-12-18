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
#define  LUA_TFUNCTION 129 
#define  LUA_TTABLE 128 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mark_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mark_object(lua_State *L, lua_State *dL) {
	switch (lua_type(L, -1)) {
	case LUA_TTABLE:
		mark_table(L, dL);
		break;
	case LUA_TFUNCTION:
		mark_function(L, dL);
		break;
	default:
		break;
	}
}