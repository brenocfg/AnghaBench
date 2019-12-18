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
struct table {int /*<<< orphan*/ * L; } ;
struct state {int /*<<< orphan*/  ref; } ;
struct ctrl {int /*<<< orphan*/ * update; struct table* root; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DEC (int /*<<< orphan*/ *) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
releaseobj(lua_State *L) {
	struct ctrl *c = lua_touserdata(L, 1);
	struct table *tbl = c->root;
	struct state *s = lua_touserdata(tbl->L, 1);
	ATOM_DEC(&s->ref);
	c->root = NULL;
	c->update = NULL;

	return 0;
}