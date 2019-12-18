#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* luasocket_scripts_modules ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void luaopen_luasocket_scripts(lua_State* L)
{
    luaL_Reg* lib = luasocket_scripts_modules;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lib->func(L);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);
}