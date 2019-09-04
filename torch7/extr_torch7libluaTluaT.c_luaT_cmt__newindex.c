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
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 

int luaT_cmt__newindex(lua_State *L)
{
  if(!lua_istable(L, 1))
    luaL_error(L, "internal error in __newindex: not a constructor table");

  if(!lua_getmetatable(L, 1))
    luaL_error(L, "internal error in __newindex: no metatable available");

  lua_pushstring(L, "__metatable");
  lua_rawget(L, -2);

  if(!lua_istable(L, -1))
    luaL_error(L, "internal error in __newindex: no metaclass available");

  lua_insert(L, 2);
  lua_pop(L, 1); /* remove the metatable over the constructor table */

  lua_rawset(L, -3);

  return 0;
}