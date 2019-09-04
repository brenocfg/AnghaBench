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
typedef  int /*<<< orphan*/  lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/ * getthread (int /*<<< orphan*/ *,int*) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_checkany (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setlocal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int db_setlocal (lua_State *L) {
  int arg;
  lua_State *L1 = getthread(L, &arg);
  lua_Debug ar;
  if (!lua_getstack(L1, luaL_checkint(L, arg+1), &ar))  /* out of range? */
    return luaL_argerror(L, arg+1, "level out of range");
  luaL_checkany(L, arg+3);
  lua_settop(L, arg+3);
  lua_xmove(L, L1, 1);
  lua_pushstring(L, lua_setlocal(L1, &ar, luaL_checkint(L, arg+2)));
  return 1;
}