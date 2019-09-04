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
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int luaT_mt__index(lua_State *L)
{
  if(!lua_getmetatable(L, 1))
    luaL_error(L, "critical internal indexing error: no metatable found");

  if(!lua_istable(L, -1))
    luaL_error(L, "critical internal indexing error: not a metatable");

  /* test for __index__ method first */
  lua_getfield(L, -1, "__index__");
  if(!lua_isnil(L, -1))
  {
    int result;

    if(!lua_isfunction(L, -1))
      luaL_error(L, "critical internal indexing error: __index__ is not a function");

    lua_pushvalue(L, 1);
    lua_pushvalue(L, 2);

    lua_call(L, 2, LUA_MULTRET); /* DEBUG: risque: faut vraiment retourner 1 ou 2 valeurs... */

    result = lua_toboolean(L, -1);
    lua_pop(L, 1);

    if(result)
      return 1;

    /* on the stack: 1. the object 2. the value 3. the metatable */
    /* apparently, __index wants only one element returned */
    /* return lua_gettop(L)-3; */

  }
  else
    lua_pop(L, 1); /* remove nil __index__ on the stack */

  lua_pushvalue(L, 2);
  lua_gettable(L, -2);

  return 1;
}