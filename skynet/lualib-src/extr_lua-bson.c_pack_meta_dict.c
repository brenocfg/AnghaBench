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
struct bson {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int LUA_TNIL ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_copy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pack_dict_data (int /*<<< orphan*/ *,struct bson*,int,int) ; 
 int reserve_length (struct bson*) ; 
 int /*<<< orphan*/  write_byte (struct bson*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_length (struct bson*,scalar_t__,int) ; 

__attribute__((used)) static void
pack_meta_dict(lua_State *L, struct bson *b, int depth) {
	int length = reserve_length(b);

	lua_pushvalue(L, -2); // push meta_obj
	lua_call(L, 1, 3); // call __pairs_func => next_func, t_data, first_k
	for(;;) {
		lua_pushvalue(L, -2); // copy data
		lua_pushvalue(L, -2); // copy k
		lua_copy(L, -5, -3); // copy next_func replace old_k
		lua_call(L, 2, 2); // call next_func

		int kt = lua_type(L, -2);
		if (kt == LUA_TNIL) {
			lua_pop(L, 4); // pop all k, v, next_func, obj
			break;
		}
		pack_dict_data(L, b, depth, kt);
	}
	write_byte(b,0);
	write_length(b, b->size - length, length);
}