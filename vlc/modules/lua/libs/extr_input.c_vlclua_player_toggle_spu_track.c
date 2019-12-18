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
 int /*<<< orphan*/  SPU_ES ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int vlclua_player_toggle_track_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vlclua_player_toggle_spu_track(lua_State *L)
{
    int id = luaL_checkinteger(L, 1);
    return vlclua_player_toggle_track_(L, SPU_ES, id);
}