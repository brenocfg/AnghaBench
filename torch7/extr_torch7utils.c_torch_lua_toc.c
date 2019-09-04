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
typedef  scalar_t__ lua_Number ;

/* Variables and functions */
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 double real_time () ; 

__attribute__((used)) static int torch_lua_toc(lua_State* L)
{
  double toctime = real_time();
  lua_Number tictime = luaL_checknumber(L,1);
  lua_pushnumber(L,toctime-tictime);
  return 1;
}