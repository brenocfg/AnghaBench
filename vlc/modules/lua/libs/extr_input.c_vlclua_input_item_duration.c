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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_GetDuration (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secf_from_vlc_tick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlclua_input_item_get_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_input_item_duration( lua_State *L )
{
    vlc_tick_t duration = input_item_GetDuration( vlclua_input_item_get_internal( L ) );
    lua_pushnumber( L, secf_from_vlc_tick(duration) );
    return 1;
}