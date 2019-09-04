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
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 double modf (int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static int math_modf (lua_State *L) {
  double ip;
  double fp = modf(luaL_checknumber(L, 1), &ip);
  lua_pushnumber(L, ip);
  lua_pushnumber(L, fp);
  return 2;
}