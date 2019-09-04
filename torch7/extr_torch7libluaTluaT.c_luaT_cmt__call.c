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
 int /*<<< orphan*/  LUA_MULTRET ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 

int luaT_cmt__call(lua_State *L)
{
  if(!lua_istable(L, 1))
    luaL_error(L, "internal error in __call: not a constructor table");

  if(!lua_getmetatable(L, 1))
    luaL_error(L, "internal error in __call: no metatable available");

  lua_pushstring(L, "__new");
  lua_rawget(L, -2);

  if(lua_isnil(L, -1))
    luaL_error(L, "no constructor available");

  lua_remove(L, 1); /* remove constructor atable */
  lua_insert(L, 1); /* insert constructor */
  lua_pop(L, 1);    /* remove fancy metatable */

  lua_call(L, lua_gettop(L)-1, LUA_MULTRET);
  return lua_gettop(L);
}