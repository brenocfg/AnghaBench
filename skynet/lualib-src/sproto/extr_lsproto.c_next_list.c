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
struct encode_ud {int /*<<< orphan*/  array_index; scalar_t__ iter_key; scalar_t__ iter_table; scalar_t__ iter_func; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int lua_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
next_list(lua_State *L, struct encode_ud * self) {
	// todo: check the key is equal to mainindex value
	if (self->iter_func) {
		lua_pushvalue(L, self->iter_func);
		lua_pushvalue(L, self->iter_table);
		lua_pushvalue(L, self->iter_key);
		lua_call(L, 2, 2);
		if (lua_isnil(L, -2)) {
			lua_pop(L, 2);
			return 0;
		}
		return 1;
	} else {
		lua_pushvalue(L,self->iter_key);
		return lua_next(L, self->array_index);
	}
}