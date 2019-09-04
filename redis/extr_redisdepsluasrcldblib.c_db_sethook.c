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
typedef  int /*<<< orphan*/ * lua_Hook ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/  gethooktable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getthread (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * hookf ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_optint (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_sethook (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int makemask (char const*,int) ; 

__attribute__((used)) static int db_sethook (lua_State *L) {
  int arg, mask, count;
  lua_Hook func;
  lua_State *L1 = getthread(L, &arg);
  if (lua_isnoneornil(L, arg+1)) {
    lua_settop(L, arg+1);
    func = NULL; mask = 0; count = 0;  /* turn off hooks */
  }
  else {
    const char *smask = luaL_checkstring(L, arg+2);
    luaL_checktype(L, arg+1, LUA_TFUNCTION);
    count = luaL_optint(L, arg+3, 0);
    func = hookf; mask = makemask(smask, count);
  }
  gethooktable(L);
  lua_pushlightuserdata(L, L1);
  lua_pushvalue(L, arg+1);
  lua_rawset(L, -3);  /* set new hook */
  lua_pop(L, 1);  /* remove hook table */
  lua_sethook(L1, func, mask, count);  /* set hooks */
  return 0;
}