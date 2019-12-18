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
struct luaL_Reg {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaT_registeratname (int /*<<< orphan*/ *,struct luaL_Reg const*,char const*) ; 

void luaT_registeratid(lua_State *L, const struct luaL_Reg *methods, const char *id)
{
  luaT_registeratname(L, methods, id);
}