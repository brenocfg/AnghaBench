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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 

long luaT_tolong(lua_State *L, int idx)
{
#if LUA_VERSION_NUM == 503
  if (sizeof(lua_Integer) >= sizeof(long) || sizeof(lua_Number) <= sizeof(lua_Integer)) {
    return (long)lua_tointeger(L, idx);
  } else {
    return (long)lua_tonumber(L, idx);
  }
#else
  return (long)lua_tonumber(L, idx);
#endif
}