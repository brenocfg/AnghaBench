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
struct table {int /*<<< orphan*/  sizehash; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct table* get_table (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lhashlen(lua_State *L) {
	struct table *tbl = get_table(L,1);
	lua_pushinteger(L, tbl->sizehash);
	return 1;
}