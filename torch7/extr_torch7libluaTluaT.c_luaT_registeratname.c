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
struct luaL_Reg {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaT_setfuncs (int /*<<< orphan*/ *,struct luaL_Reg const*,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 

void luaT_registeratname(lua_State *L, const struct luaL_Reg *methods, const char *name)
{
  int idx = lua_gettop(L);

  luaL_checktype(L, idx, LUA_TTABLE);
  lua_pushstring(L, name);
  lua_rawget(L, idx);

  if(lua_isnil(L, -1))
  {
    lua_pop(L, 1);
    lua_pushstring(L, name);
    lua_newtable(L);
    lua_rawset(L, idx);

    lua_pushstring(L, name);
    lua_rawget(L, idx);
  }

  luaT_setfuncs(L, methods, 0);
  lua_pop(L, 1);
}