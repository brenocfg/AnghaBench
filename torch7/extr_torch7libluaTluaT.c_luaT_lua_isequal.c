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
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  luaT_typename (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int lua_rawequal (int /*<<< orphan*/ *,int,int) ; 
 void** lua_touserdata (int /*<<< orphan*/ *,int) ; 

int luaT_lua_isequal(lua_State *L)
{
  if(lua_isuserdata(L, 1) && lua_isuserdata(L, 2))
  {
    void **u1, **u2;
    luaL_argcheck(L, luaT_typename(L, 1), 1, "Torch object expected");
    luaL_argcheck(L, luaT_typename(L, 2), 2, "Torch object expected");

    u1 = lua_touserdata(L, 1);
    u2 = lua_touserdata(L, 2);
    if(*u1 == *u2)
      lua_pushboolean(L, 1);
    else
      lua_pushboolean(L, 0);
  }
  else if(lua_istable(L, 1) && lua_istable(L, 2))
    lua_pushboolean(L, lua_rawequal(L, 1, 2));
  else
    lua_pushboolean(L, 0);
  return 1;
}