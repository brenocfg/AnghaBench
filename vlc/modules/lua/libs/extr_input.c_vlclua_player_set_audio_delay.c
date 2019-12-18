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
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_PLAYER_WHENCE_ABSOLUTE ; 
 double luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SetAudioDelay (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tick_from_sec (double) ; 
 int /*<<< orphan*/ * vlclua_get_player_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_player_set_audio_delay(lua_State *L)
{
    vlc_player_t *player = vlclua_get_player_internal(L);

    double delay_sec = luaL_checknumber(L, 1);
    vlc_tick_t delay = vlc_tick_from_sec(delay_sec);

    vlc_player_Lock(player);
    vlc_player_SetAudioDelay(player, delay, VLC_PLAYER_WHENCE_ABSOLUTE);
    vlc_player_Unlock(player);

    return 0;
}