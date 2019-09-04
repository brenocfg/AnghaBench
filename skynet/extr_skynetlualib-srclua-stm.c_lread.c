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
struct stm_copy {int /*<<< orphan*/  sz; int /*<<< orphan*/  msg; } ;
struct boxreader {struct stm_copy* lastcopy; int /*<<< orphan*/  obj; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_MULTRET ; 
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 struct boxreader* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 struct stm_copy* stm_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm_releasecopy (struct stm_copy*) ; 

__attribute__((used)) static int
lread(lua_State *L) {
	struct boxreader * box = lua_touserdata(L, 1);
	luaL_checktype(L, 2, LUA_TFUNCTION);

	struct stm_copy * copy = stm_copy(box->obj);
	if (copy == box->lastcopy) {
		// not update
		stm_releasecopy(copy);
		lua_pushboolean(L, 0);
		return 1;
	}

	stm_releasecopy(box->lastcopy);
	box->lastcopy = copy;
	if (copy) {
		lua_settop(L, 3);
		lua_replace(L, 1);
		lua_settop(L, 2);
		lua_pushlightuserdata(L, copy->msg);
		lua_pushinteger(L, copy->sz);
		lua_pushvalue(L, 1);
		lua_call(L, 3, LUA_MULTRET);
		lua_pushboolean(L, 1);
		lua_replace(L, 1);
		return lua_gettop(L);
	} else {
		lua_pushboolean(L, 0);
		return 1;
	}
}