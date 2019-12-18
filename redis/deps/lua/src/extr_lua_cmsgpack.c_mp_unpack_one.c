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
 int luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,scalar_t__) ; 
 int mp_unpack_full (int /*<<< orphan*/ *,int,int) ; 

int mp_unpack_one(lua_State *L) {
    int offset = luaL_optinteger(L, 2, 0);
    /* Variable pop because offset may not exist */
    lua_pop(L, lua_gettop(L)-1);
    return mp_unpack_full(L, 1, offset);
}