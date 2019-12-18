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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ VLC_PLAYER_STATE_PAUSED ; 
 scalar_t__ vlc_player_GetState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Pause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_pause(lua_State *L)
{
    /* this is in fact a toggle pause */
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);
    vlc_player_t *player = vlc_playlist_GetPlayer(playlist);

    vlc_player_Lock(player);
    if (vlc_player_GetState(player) != VLC_PLAYER_STATE_PAUSED)
        vlc_player_Pause(player);
    else
        vlc_player_Resume(player);
    vlc_player_Unlock(player);

    return 0;
}