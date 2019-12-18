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
 int /*<<< orphan*/  is_marked (int /*<<< orphan*/ *,void const*) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 void* lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mark_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marked (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static void mark_table(lua_State *L, lua_State *dL) {
	const void *p = lua_topointer(L, -1);
	int len = 0;
	
	if (!is_marked(dL, p)) {
		marked(dL, p, 0);

		lua_pushnil(L);
		while (lua_next(L, -2) != 0) {
			++len;
			mark_object(L, dL);
			lua_pop(L, 1);
			mark_object(L, dL);
		}
		
		marked(dL, p, len);
	}
}