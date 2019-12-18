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
struct table {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 struct table* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct table *
get_table(lua_State *L, int index) {
	struct table *tbl = lua_touserdata(L,index);
	if (tbl == NULL) {
		luaL_error(L, "Need a conf object");
	}
	return tbl;
}