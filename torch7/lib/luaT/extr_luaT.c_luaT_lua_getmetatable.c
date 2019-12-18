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
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaT_pushmetatable (int /*<<< orphan*/ *,char const*) ; 

int luaT_lua_getmetatable(lua_State *L)
{
  const char *tname = luaL_checkstring(L, 1);
  if(luaT_pushmetatable(L, tname))
    return 1;
  return 0;
}