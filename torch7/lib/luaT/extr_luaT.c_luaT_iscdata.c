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
 int /*<<< orphan*/  CDATA_MT_KEY ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int LUA_TUSERDATA ; 
 int /*<<< orphan*/  cdatamt ; 
 scalar_t__ luaL_dostring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lua_rawequal (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int luaT_iscdata(lua_State *L, int ud)
{
  int type = lua_type(L, ud);
  if(type == 10)
    return 1;
  if(type != LUA_TUSERDATA)
    return 0;
  if(!lua_getmetatable(L, ud))
    return 0;

  lua_pushlightuserdata(L, CDATA_MT_KEY);
  lua_rawget(L, LUA_REGISTRYINDEX);
  if (lua_isnil(L, -1))
  {
    // initialize cdata metatable
    lua_pop(L, 1);
    if(luaL_dostring(L, cdatamt))
      luaL_error(L, "internal error (could not load cdata mt): %s", lua_tostring(L, -1));

    lua_pushlightuserdata(L, CDATA_MT_KEY);
    lua_pushvalue(L, -2);
    lua_rawset(L, LUA_REGISTRYINDEX);
  }

  int iscdata = lua_rawequal(L, -1, -2);
  lua_pop(L, 2);
  return iscdata;
}