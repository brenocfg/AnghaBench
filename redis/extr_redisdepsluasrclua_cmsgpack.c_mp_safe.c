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
 int /*<<< orphan*/  LUA_MULTRET ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 

int mp_safe(lua_State *L) {
    int argc, err, total_results;

    argc = lua_gettop(L);

    /* This adds our function to the bottom of the stack
     * (the "call this function" position) */
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_insert(L, 1);

    err = lua_pcall(L, argc, LUA_MULTRET, 0);
    total_results = lua_gettop(L);

    if (!err) {
        return total_results;
    } else {
        lua_pushnil(L);
        lua_insert(L,-2);
        return 2;
    }
}