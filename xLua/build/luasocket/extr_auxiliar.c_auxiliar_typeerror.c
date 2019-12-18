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
 int luaL_argerror (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 char* lua_pushfstring (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 

int auxiliar_typeerror (lua_State *L, int narg, const char *tname) {
  const char *msg = lua_pushfstring(L, "%s expected, got %s", tname, 
      luaL_typename(L, narg));
  return luaL_argerror(L, narg, msg);
}