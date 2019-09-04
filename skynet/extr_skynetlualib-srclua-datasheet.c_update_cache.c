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
struct proxy {void const* data; int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TUSERDATA ; 
 int /*<<< orphan*/  NODECACHE ; 
 int /*<<< orphan*/  PROXYCACHE ; 
 int /*<<< orphan*/  clear_table (int /*<<< orphan*/ *) ; 
 struct table* gettable (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawsetp (int /*<<< orphan*/ *,int,struct table const*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 struct proxy* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_upvalueindex (int) ; 

__attribute__((used)) static void
update_cache(lua_State *L, const void *data, const void * newdata) {
	lua_getfield(L, LUA_REGISTRYINDEX, NODECACHE);
	int t = lua_gettop(L);
	lua_getfield(L, LUA_REGISTRYINDEX, PROXYCACHE);
	int pt = t + 1;
	lua_newtable(L);	// temp table
	int nt = pt + 1;
	lua_pushnil(L);
	while (lua_next(L, t) != 0) {
		// pointer (-2) -> table (-1)
		lua_pushvalue(L, -1);
		if (lua_rawget(L, pt) == LUA_TUSERDATA) {
			// pointer, table, proxy
			struct proxy * p = lua_touserdata(L, -1);
			if (p->data == data) {
				// update to newdata
				p->data = newdata;
				const struct table * newt = gettable(newdata, p->index);
				lua_pop(L, 1);
				// pointer, table
				clear_table(L);
				lua_pushvalue(L, lua_upvalueindex(1));
				// pointer, table, meta
				lua_setmetatable(L, -2);
				// pointer, table
				if (newt) {
					lua_rawsetp(L, nt, newt);
				} else {
					lua_pop(L, 1);
				}
				// pointer
				lua_pushvalue(L, -1);
				lua_pushnil(L);
				lua_rawset(L, t);
			} else {
				lua_pop(L, 2);
			}
		} else {
			lua_pop(L, 2);
			// pointer
		}
	}
	// copy nt to t
	lua_pushnil(L);
	while (lua_next(L, nt) != 0) {
		lua_pushvalue(L, -2);
		lua_insert(L, -2);
		// key key value
		lua_rawset(L, t);
	}
	// NODECACHE PROXYCACHE TEMP
	lua_pop(L, 3);
}