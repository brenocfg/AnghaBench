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
typedef  int /*<<< orphan*/  uint8_t ;
struct write_block {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINE_TYPE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LUA_TNIL ; 
 int /*<<< orphan*/  TYPE_TABLE ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_copy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pack_one (int /*<<< orphan*/ *,struct write_block*,int,int) ; 
 int /*<<< orphan*/  wb_nil (struct write_block*) ; 
 int /*<<< orphan*/  wb_push (struct write_block*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
wb_table_metapairs(lua_State *L, struct write_block *wb, int index, int depth) {
	uint8_t n = COMBINE_TYPE(TYPE_TABLE, 0);
	wb_push(wb, &n, 1);
	lua_pushvalue(L, index);
	lua_call(L, 1, 3);
	for(;;) {
		lua_pushvalue(L, -2);
		lua_pushvalue(L, -2);
		lua_copy(L, -5, -3);
		lua_call(L, 2, 2);
		int type = lua_type(L, -2);
		if (type == LUA_TNIL) {
			lua_pop(L, 4);
			break;
		}
		pack_one(L, wb, -2, depth);
		pack_one(L, wb, -1, depth);
		lua_pop(L, 1);
	}
	wb_nil(wb);
}