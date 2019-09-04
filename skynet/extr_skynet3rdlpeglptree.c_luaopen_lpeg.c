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
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  MAXBACK ; 
 char* MAXSTACKIDX ; 
 int /*<<< orphan*/  PATTERN_T ; 
 int /*<<< orphan*/  luaL_newlib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_newmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_setfuncs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  metareg ; 
 int /*<<< orphan*/  pattreg ; 

int luaopen_lpeg (lua_State *L) {
  luaL_newmetatable(L, PATTERN_T);
  lua_pushnumber(L, MAXBACK);  /* initialize maximum backtracking */
  lua_setfield(L, LUA_REGISTRYINDEX, MAXSTACKIDX);
  luaL_setfuncs(L, metareg, 0);
  luaL_newlib(L, pattreg);
  lua_pushvalue(L, -1);
  lua_setfield(L, -3, "__index");
  return 1;
}