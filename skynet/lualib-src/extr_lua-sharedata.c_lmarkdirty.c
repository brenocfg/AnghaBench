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
struct table {int /*<<< orphan*/  L; } ;
struct state {int dirty; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct table* get_table (int /*<<< orphan*/ *,int) ; 
 struct state* lua_touserdata (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lmarkdirty(lua_State *L) {
	struct table *tbl = get_table(L,1);
	struct state * s = lua_touserdata(tbl->L, 1);
	s->dirty = 1;
	return 0;
}