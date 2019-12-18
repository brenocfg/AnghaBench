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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  lua_Integer ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 

ptrdiff_t luaT_checkinteger(lua_State *L, int idx)
{
#if LUA_VERSION_NUM >= 503
  if (sizeof(lua_Integer) >= sizeof(ptrdiff_t) || sizeof(lua_Number) <= sizeof(lua_Integer)) {
    return (ptrdiff_t)luaL_checkinteger(L, idx);
  } else {
    return (ptrdiff_t)luaL_checknumber(L, idx);
  }
#else
  return (ptrdiff_t)luaL_checknumber(L, idx);
#endif
}