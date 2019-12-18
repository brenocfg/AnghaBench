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
 char* findfile (int /*<<< orphan*/ *,char const*,char*) ; 
 scalar_t__ ll_loadfunc (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  loaderror (int /*<<< orphan*/ *,char const*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 char* mkfuncname (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int loader_C (lua_State *L) {
  const char *funcname;
  const char *name = luaL_checkstring(L, 1);
  const char *filename = findfile(L, name, "cpath");
  if (filename == NULL) return 1;  /* library not found in this path */
  funcname = mkfuncname(L, name);
  if (ll_loadfunc(L, filename, funcname) != 0)
    loaderror(L, filename);
  return 1;  /* library loaded successfully */
}