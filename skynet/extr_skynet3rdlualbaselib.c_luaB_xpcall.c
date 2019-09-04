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
 int /*<<< orphan*/  LUA_MULTRET ; 
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int finishpcall (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_pcallk (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int (*) (int /*<<< orphan*/ *,int,int)) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rotate (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int luaB_xpcall (lua_State *L) {
  int status;
  int n = lua_gettop(L);
  luaL_checktype(L, 2, LUA_TFUNCTION);  /* check error function */
  lua_pushboolean(L, 1);  /* first result */
  lua_pushvalue(L, 1);  /* function */
  lua_rotate(L, 3, 2);  /* move them below function's arguments */
  status = lua_pcallk(L, n - 2, LUA_MULTRET, 2, 2, finishpcall);
  return finishpcall(L, status, 2);
}