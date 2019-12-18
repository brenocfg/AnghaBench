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
 int /*<<< orphan*/  auxiliar_add2group (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  auxiliar_newclass (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  global_create ; 
 int /*<<< orphan*/  luaL_openlib (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unix_methods ; 

int luaopen_socket_unix(lua_State *L) {
    /* create classes */
    auxiliar_newclass(L, "unix{master}", unix_methods);
    auxiliar_newclass(L, "unix{client}", unix_methods);
    auxiliar_newclass(L, "unix{server}", unix_methods);
    /* create class groups */
    auxiliar_add2group(L, "unix{master}", "unix{any}");
    auxiliar_add2group(L, "unix{client}", "unix{any}");
    auxiliar_add2group(L, "unix{server}", "unix{any}");
#if LUA_VERSION_NUM > 501 && !defined(LUA_COMPAT_MODULE)
    lua_pushcfunction(L, global_create);
    (void) func;
#else
    /* set function into socket namespace */
    luaL_openlib(L, "socket", func, 0);
    lua_pushcfunction(L, global_create);
#endif
    /* return the function instead of the 'socket' table */
    return 1;
}