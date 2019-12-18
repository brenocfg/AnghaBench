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
 char* LUA_DBLIBNAME ; 
 char* LUA_LOADLIBNAME ; 
 char* LUA_MATHLIBNAME ; 
 char* LUA_OSLIBNAME ; 
 char* LUA_STRLIBNAME ; 
 char* LUA_TABLIBNAME ; 
 int /*<<< orphan*/  luaLoadLib (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaopen_base ; 
 int /*<<< orphan*/  luaopen_bit ; 
 int /*<<< orphan*/  luaopen_cjson ; 
 int /*<<< orphan*/  luaopen_cmsgpack ; 
 int /*<<< orphan*/  luaopen_debug ; 
 int /*<<< orphan*/  luaopen_math ; 
 int /*<<< orphan*/  luaopen_os ; 
 int /*<<< orphan*/  luaopen_package ; 
 int /*<<< orphan*/  luaopen_string ; 
 int /*<<< orphan*/  luaopen_struct ; 
 int /*<<< orphan*/  luaopen_table ; 

void luaLoadLibraries(lua_State *lua) {
    luaLoadLib(lua, "", luaopen_base);
    luaLoadLib(lua, LUA_TABLIBNAME, luaopen_table);
    luaLoadLib(lua, LUA_STRLIBNAME, luaopen_string);
    luaLoadLib(lua, LUA_MATHLIBNAME, luaopen_math);
    luaLoadLib(lua, LUA_DBLIBNAME, luaopen_debug);
    luaLoadLib(lua, "cjson", luaopen_cjson);
    luaLoadLib(lua, "struct", luaopen_struct);
    luaLoadLib(lua, "cmsgpack", luaopen_cmsgpack);
    luaLoadLib(lua, "bit", luaopen_bit);

#if 0 /* Stuff that we don't load currently, for sandboxing concerns. */
    luaLoadLib(lua, LUA_LOADLIBNAME, luaopen_package);
    luaLoadLib(lua, LUA_OSLIBNAME, luaopen_os);
#endif
}