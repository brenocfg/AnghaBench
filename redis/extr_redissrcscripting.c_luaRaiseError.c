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
 int lua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 

int luaRaiseError(lua_State *lua) {
    lua_pushstring(lua,"err");
    lua_gettable(lua,-2);
    return lua_error(lua);
}