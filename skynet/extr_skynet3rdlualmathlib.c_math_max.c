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
 int /*<<< orphan*/  LUA_OPLT ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ lua_compare (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int math_max (lua_State *L) {
  int n = lua_gettop(L);  /* number of arguments */
  int imax = 1;  /* index of current maximum value */
  int i;
  luaL_argcheck(L, n >= 1, 1, "value expected");
  for (i = 2; i <= n; i++) {
    if (lua_compare(L, imax, i, LUA_OPLT))
      imax = i;
  }
  lua_pushvalue(L, imax);
  return 1;
}