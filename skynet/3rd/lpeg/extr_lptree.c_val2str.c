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
 char const* luaL_typename (int /*<<< orphan*/ *,int) ; 
 char const* lua_pushfstring (int /*<<< orphan*/ *,char*,char const*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char *val2str (lua_State *L, int idx) {
  const char *k = lua_tostring(L, idx);
  if (k != NULL)
    return lua_pushfstring(L, "%s", k);
  else
    return lua_pushfstring(L, "(a %s)", luaL_typename(L, idx));
}