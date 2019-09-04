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
struct proxy {int index; void const* data; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  NODECACHE ; 
 int /*<<< orphan*/  PROXYCACHE ; 
 struct table* gettable (void const*,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 struct proxy* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_rawgetp (int /*<<< orphan*/ *,int,struct table const*) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawsetp (int /*<<< orphan*/ *,int,struct table const*) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int lua_upvalueindex (int) ; 

__attribute__((used)) static void
create_proxy(lua_State *L, const void *data, int index) {
	const struct table * t = gettable(data, index);
	if (t == NULL) {
		luaL_error(L, "Invalid index %d", index);
	}
	lua_getfield(L, LUA_REGISTRYINDEX, NODECACHE);
	if (lua_rawgetp(L, -1, t) == LUA_TTABLE) {
		lua_replace(L, -2);
		return;
	}
	lua_pop(L, 1);
	lua_newtable(L);
	lua_pushvalue(L, lua_upvalueindex(1));
	lua_setmetatable(L, -2);
	lua_pushvalue(L, -1);
	// NODECACHE, table, table
	lua_rawsetp(L, -3, t);
	// NODECACHE, table
	lua_getfield(L, LUA_REGISTRYINDEX, PROXYCACHE);
	// NODECACHE, table, PROXYCACHE
	lua_pushvalue(L, -2);
	// NODECACHE, table, PROXYCACHE, table
	struct proxy * p = lua_newuserdata(L, sizeof(struct proxy));
	// NODECACHE, table, PROXYCACHE, table, proxy
	p->data = data;
	p->index = index;
	lua_rawset(L, -3);
	// NODECACHE, table, PROXYCACHE
	lua_pop(L, 1);
	// NODECACHE, table
	lua_replace(L, -2);
	// table
}