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
 int /*<<< orphan*/  COMBINE_TYPE (int /*<<< orphan*/ ,int) ; 
 int MAX_COOKIE ; 
 int /*<<< orphan*/  TYPE_TABLE ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pack_one (int /*<<< orphan*/ *,struct write_block*,int,int) ; 
 int /*<<< orphan*/  wb_integer (struct write_block*,int) ; 
 int /*<<< orphan*/  wb_push (struct write_block*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
wb_table_array(lua_State *L, struct write_block * wb, int index, int depth) {
	int array_size = lua_rawlen(L,index);
	if (array_size >= MAX_COOKIE-1) {
		uint8_t n = COMBINE_TYPE(TYPE_TABLE, MAX_COOKIE-1);
		wb_push(wb, &n, 1);
		wb_integer(wb, array_size);
	} else {
		uint8_t n = COMBINE_TYPE(TYPE_TABLE, array_size);
		wb_push(wb, &n, 1);
	}

	int i;
	for (i=1;i<=array_size;i++) {
		lua_rawgeti(L,index,i);
		pack_one(L, wb, -1, depth);
		lua_pop(L,1);
	}

	return array_size;
}