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
 int luaL_error (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int luaL_typerror(lua_State *L, int narg, const char *tname)
{
  return luaL_error(L, "%s expected, got %s", tname, luaL_typename(L, narg));
}