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
 int luaT_checkboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 

int luaT_optboolean(lua_State *L, int ud, int def)
{
  if(lua_isnoneornil(L,ud))
    return def;

  return luaT_checkboolean(L, ud);
}