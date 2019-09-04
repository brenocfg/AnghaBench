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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  luaT_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int luaT_mt__newindex(lua_State *L)
{
  if(!lua_getmetatable(L, 1))
    luaL_error(L, "critical internal indexing error: no metatable found");

  if(!lua_istable(L, -1))
    luaL_error(L, "critical internal indexing error: not a metatable");

  /* test for __newindex__ method first */
  lua_getfield(L, -1, "__newindex__");
  if(!lua_isnil(L, -1))
  {
    int result;

    if(!lua_isfunction(L, -1))
      luaL_error(L, "critical internal indexing error: __newindex__ is not a function");

    lua_pushvalue(L, 1);
    lua_pushvalue(L, 2);
    lua_pushvalue(L, 3);

    lua_call(L, 3, 1); /* DEBUG: risque: faut vraiment retourner qqch */

    result = lua_toboolean(L, -1);
    lua_pop(L, 1);

    if(result)
      return 0;
  }
  else
    lua_pop(L, 1); /* remove nil __newindex__ on the stack */

  lua_pop(L, 1);    /* pop the metatable */
  if(lua_istable(L, 1))
    lua_rawset(L, 1);
  else
    luaL_error(L, "the class %s cannot be indexed", luaT_typename(L, 1));

  return 0;
}