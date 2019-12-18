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
struct write_block {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_MINSTACK ; 
 scalar_t__ LUA_TNIL ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_getmetafield (int /*<<< orphan*/ *,int,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int wb_table_array (int /*<<< orphan*/ *,struct write_block*,int,int) ; 
 int /*<<< orphan*/  wb_table_hash (int /*<<< orphan*/ *,struct write_block*,int,int,int) ; 
 int /*<<< orphan*/  wb_table_metapairs (int /*<<< orphan*/ *,struct write_block*,int,int) ; 

__attribute__((used)) static void
wb_table(lua_State *L, struct write_block *wb, int index, int depth) {
	luaL_checkstack(L, LUA_MINSTACK, NULL);
	if (index < 0) {
		index = lua_gettop(L) + index + 1;
	}
	if (luaL_getmetafield(L, index, "__pairs") != LUA_TNIL) {
		wb_table_metapairs(L, wb, index, depth);
	} else {
		int array_size = wb_table_array(L, wb, index, depth);
		wb_table_hash(L, wb, index, depth, array_size);
	}
}