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
 int /*<<< orphan*/ * LUA_IGMARK ; 
 char* luaL_gsub (int /*<<< orphan*/ *,char const*,char*,char*) ; 
 char* lua_pushfstring (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *mksymname(lua_State *L, const char *modname,
			     const char *prefix)
{
  const char *funcname;
  const char *mark = strchr(modname, *LUA_IGMARK);
  if (mark) modname = mark + 1;
  funcname = luaL_gsub(L, modname, ".", "_");
  funcname = lua_pushfstring(L, prefix, funcname);
  lua_remove(L, -2);  /* remove 'gsub' result */
  return funcname;
}