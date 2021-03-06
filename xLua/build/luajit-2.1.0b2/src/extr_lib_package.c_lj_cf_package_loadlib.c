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
 int PACKAGE_ERR_LIB ; 
 char* PACKAGE_LIB_FAIL ; 
 int ll_loadfunc (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int lj_cf_package_loadlib(lua_State *L)
{
  const char *path = luaL_checkstring(L, 1);
  const char *init = luaL_checkstring(L, 2);
  int st = ll_loadfunc(L, path, init, 1);
  if (st == 0) {  /* no errors? */
    return 1;  /* return the loaded function */
  } else {  /* error; error message is on stack top */
    lua_pushnil(L);
    lua_insert(L, -2);
    lua_pushstring(L, (st == PACKAGE_ERR_LIB) ?  PACKAGE_LIB_FAIL : "init");
    return 3;  /* return nil, error message, and where */
  }
}