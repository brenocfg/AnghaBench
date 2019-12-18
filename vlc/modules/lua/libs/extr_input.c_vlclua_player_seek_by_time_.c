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
typedef  enum vlc_player_whence { ____Placeholder_vlc_player_whence } vlc_player_whence ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_PLAYER_SEEK_PRECISE ; 
 int /*<<< orphan*/  VLC_TICK_FROM_US (int) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SeekByTime (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_player_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_player_seek_by_time_(lua_State *L,
                                       enum vlc_player_whence whence)
{
    int usec = luaL_checkinteger(L, 1);
    vlc_tick_t time = VLC_TICK_FROM_US(usec);

    vlc_player_t *player = vlclua_get_player_internal(L);

    vlc_player_Lock(player);
    vlc_player_SeekByTime(player, time, VLC_PLAYER_SEEK_PRECISE, whence);
    vlc_player_Unlock(player);

    return 0;
}