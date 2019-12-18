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
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  cdataname ; 
 scalar_t__ luaL_dostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char* luaT_cdataname(lua_State *L, int ud, const char *tname)
{
  lua_pushstring(L, "__cdataname");
  lua_rawget(L, LUA_REGISTRYINDEX);
  if(lua_isnil(L,-1))
  {
    lua_pop(L, 1);

    if(luaL_dostring(L, cdataname)) /* did something go wrong? */
      luaL_error(L, "internal error (could not load cdataname): %s", lua_tostring(L, -1));

    lua_pushstring(L, "__cdataname");
    lua_pushvalue(L, -2);
    lua_rawset(L, LUA_REGISTRYINDEX);
  }
  if(!lua_isfunction(L, -1)) /* should not happen */
    luaL_error(L, "internal error (cdataname is not a function)");

  lua_pushvalue(L, ud);
  if(tname)
    lua_pushstring(L, tname);
  if(lua_pcall(L, (tname ? 2 : 1), 1, 0))
    luaL_error(L, "internal error (cdataname): %s", lua_tostring(L, -1));

  tname = lua_tostring(L, -1);
  lua_pop(L, 1);

  return tname;
}