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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  ROOT_TABLE ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgetp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  lua_rawsetp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static void make_root(lua_State *L, const void *p, const char *name, int type, const char *used_in, int need_stat) {
	lua_rawgetp(L, ROOT_TABLE, p);
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L); // -- root
		lua_newtable(L); // root.used_in
		if (used_in != NULL) {
			lua_pushboolean(L, 1);
			lua_setfield(L, -2, used_in);
		}
		lua_setfield(L, -2, "used_in");
		if (need_stat) {
		    lua_pushstring(L, name);
		    lua_setfield(L, -2, "name");
		    lua_pushnumber(L, type);
		    lua_setfield(L, -2, "type");
		}
		
		lua_pushvalue(L, -1);
		lua_rawsetp(L, ROOT_TABLE, p); //ROOT_TABLE[p] = root
	} else {
		if (used_in != NULL) {
			lua_getfield(L, -1, "used_in");
			lua_pushboolean(L, 1);
			lua_setfield(L, -2, used_in);
			lua_pop(L, 1);
		}
	}
}