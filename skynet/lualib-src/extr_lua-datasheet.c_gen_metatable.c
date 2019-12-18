#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NODECACHE ; 
 int /*<<< orphan*/  PROXYCACHE ; 
 int /*<<< orphan*/  TABLES ; 
 int /*<<< orphan*/ * lindex ; 
 int /*<<< orphan*/ * llen ; 
 int /*<<< orphan*/ * lpairs ; 
 int /*<<< orphan*/  luaL_setfuncs (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_weak_table (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
gen_metatable(lua_State *L) {
	new_weak_table(L, "kv");	// NODECACHE { pointer:table }
	lua_setfield(L, LUA_REGISTRYINDEX, NODECACHE);

	new_weak_table(L, "k");	// PROXYCACHE { table:userdata }
	lua_setfield(L, LUA_REGISTRYINDEX, PROXYCACHE);

	lua_newtable(L);
	lua_setfield(L, LUA_REGISTRYINDEX, TABLES);

	lua_createtable(L, 0, 1);	// mod table

	lua_createtable(L, 0, 2);	// metatable
	luaL_Reg l[] = {
		{ "__index", lindex },
		{ "__pairs", lpairs },
		{ "__len", llen },
		{ NULL, NULL },
	};
	lua_pushvalue(L, -1);
	luaL_setfuncs(L, l, 1);
}