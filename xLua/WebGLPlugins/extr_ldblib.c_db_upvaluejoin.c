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
 int checkupval (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  lua_iscfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_upvaluejoin (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static int db_upvaluejoin (lua_State *L) {
  int n1 = checkupval(L, 1, 2);
  int n2 = checkupval(L, 3, 4);
  luaL_argcheck(L, !lua_iscfunction(L, 1), 1, "Lua function expected");
  luaL_argcheck(L, !lua_iscfunction(L, 3), 3, "Lua function expected");
  lua_upvaluejoin(L, 1, n1, 3, n2);
  return 0;
}