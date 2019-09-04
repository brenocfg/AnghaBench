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
struct state {int /*<<< orphan*/  ref; } ;
struct ctrl {int /*<<< orphan*/ * update; struct table* root; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_INC (int /*<<< orphan*/ *) ; 
 struct table* get_table (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 struct ctrl* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 struct state* lua_touserdata (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  releaseobj ; 

__attribute__((used)) static int
lboxconf(lua_State *L) {
	struct table * tbl = get_table(L,1);	
	struct state * s = lua_touserdata(tbl->L, 1);
	ATOM_INC(&s->ref);

	struct ctrl * c = lua_newuserdata(L, sizeof(*c));
	c->root = tbl;
	c->update = NULL;
	if (luaL_newmetatable(L, "confctrl")) {
		lua_pushcfunction(L, releaseobj);
		lua_setfield(L, -2, "__gc");
	}
	lua_setmetatable(L, -2);

	return 1;
}