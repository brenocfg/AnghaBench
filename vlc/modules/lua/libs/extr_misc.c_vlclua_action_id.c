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
typedef  scalar_t__ vlc_action_id_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vlc_actions_get_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlclua_action_id( lua_State *L )
{
    vlc_action_id_t i_key = vlc_actions_get_id( luaL_checkstring( L, 1 ) );
    if (i_key == 0)
        return 0;
    lua_pushnumber( L, i_key );
    return 1;
}