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
 int /*<<< orphan*/  luaL_openlib (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_setfuncs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_methods ; 

int udp_open(lua_State *L)
{
    /* create classes */
    auxiliar_newclass(L, "udp{connected}", udp_methods);
    auxiliar_newclass(L, "udp{unconnected}", udp_methods);
    /* create class groups */
    auxiliar_add2group(L, "udp{connected}",   "udp{any}");
    auxiliar_add2group(L, "udp{unconnected}", "udp{any}");
    auxiliar_add2group(L, "udp{connected}",   "select{able}");
    auxiliar_add2group(L, "udp{unconnected}", "select{able}");
    /* define library functions */
#if LUA_VERSION_NUM > 501 && !defined(LUA_COMPAT_MODULE)
    luaL_setfuncs(L, func, 0);
#else
    luaL_openlib(L, NULL, func, 0);
#endif
    return 0;
}