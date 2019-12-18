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
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaT_cdataname (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 

int luaT_lua_metatype(lua_State *L)
{
  if( (lua_gettop(L) != 2) && (lua_gettop(L) != 3) )
    luaL_error(L, "expecting: string table [ctype]");

  luaL_checkstring(L, 1);
  luaL_checktype(L, 2, LUA_TTABLE);

  if(lua_gettop(L) == 3)
  {
    if(!luaT_cdataname(L, 3, lua_tostring(L, 1)))
      luaL_error(L, "could not register cdata type -- missing ffi library?");
  }

  /* registry[name] = metatable */
  lua_pushvalue(L, 1);
  lua_pushvalue(L, 2);
  lua_rawset(L, LUA_REGISTRYINDEX);

  /* registry[metatable] = tname */
  lua_pushvalue(L, 2);
  lua_pushvalue(L, 1);
  lua_rawset(L, LUA_REGISTRYINDEX);

  return 0;
}