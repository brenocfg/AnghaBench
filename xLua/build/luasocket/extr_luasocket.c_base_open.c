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
 char* LUASOCKET_VERSION ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  luaL_openlib (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_setfuncs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ socket_open () ; 

__attribute__((used)) static int base_open(lua_State *L) {
    if (socket_open()) {
        /* export functions (and leave namespace table on top of stack) */
#if LUA_VERSION_NUM > 501 && !defined(LUA_COMPAT_MODULE)
        lua_newtable(L);
        luaL_setfuncs(L, func, 0);
#else
        luaL_openlib(L, "socket", func, 0);
#endif
#ifdef LUASOCKET_DEBUG
        lua_pushstring(L, "_DEBUG");
        lua_pushboolean(L, 1);
        lua_rawset(L, -3);
#endif
        /* make version string available to scripts */
        lua_pushstring(L, "_VERSION");
        lua_pushstring(L, LUASOCKET_VERSION);
        lua_rawset(L, -3);
        return 1;
    } else {
        lua_pushstring(L, "unable to initialize library");
        lua_error(L);
        return 0;
    }
}