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
 int /*<<< orphan*/  LJ_ERR_BADMODN ; 
 int /*<<< orphan*/  LUA_GLOBALSINDEX ; 
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  dooptions (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lj_err_callerv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * luaL_findtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  modinit (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  setfenv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lj_cf_package_module(lua_State *L)
{
  const char *modname = luaL_checkstring(L, 1);
  int loaded = lua_gettop(L) + 1;  /* index of _LOADED table */
  lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
  lua_getfield(L, loaded, modname);  /* get _LOADED[modname] */
  if (!lua_istable(L, -1)) {  /* not found? */
    lua_pop(L, 1);  /* remove previous result */
    /* try global variable (and create one if it does not exist) */
    if (luaL_findtable(L, LUA_GLOBALSINDEX, modname, 1) != NULL)
      lj_err_callerv(L, LJ_ERR_BADMODN, modname);
    lua_pushvalue(L, -1);
    lua_setfield(L, loaded, modname);  /* _LOADED[modname] = new table */
  }
  /* check whether table already has a _NAME field */
  lua_getfield(L, -1, "_NAME");
  if (!lua_isnil(L, -1)) {  /* is table an initialized module? */
    lua_pop(L, 1);
  } else {  /* no; initialize it */
    lua_pop(L, 1);
    modinit(L, modname);
  }
  lua_pushvalue(L, -1);
  setfenv(L);
  dooptions(L, loaded - 1);
  return 0;
}