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
typedef  enum vlc_player_state { ____Placeholder_vlc_player_state } vlc_player_state ;

/* Variables and functions */
#define  VLC_PLAYER_STATE_PAUSED 132 
#define  VLC_PLAYER_STATE_PLAYING 131 
#define  VLC_PLAYER_STATE_STARTED 130 
#define  VLC_PLAYER_STATE_STOPPED 129 
#define  VLC_PLAYER_STATE_STOPPING 128 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int vlc_player_GetState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_status(lua_State *L)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);

    vlc_player_t *player = vlc_playlist_GetPlayer(playlist);
    vlc_player_Lock(player);
    enum vlc_player_state state = vlc_player_GetState(player);
    vlc_player_Unlock(player);

    switch (state)
    {
        case VLC_PLAYER_STATE_STOPPED:
            lua_pushliteral(L, "stopped");
            break;
        case VLC_PLAYER_STATE_STARTED:
            lua_pushliteral(L, "started");
            break;
        case VLC_PLAYER_STATE_PLAYING:
            lua_pushliteral(L, "playing");
            break;
        case VLC_PLAYER_STATE_PAUSED:
            lua_pushliteral(L, "paused");
            break;
        case VLC_PLAYER_STATE_STOPPING:
            lua_pushliteral(L, "stopping");
            break;
        default:
            lua_pushliteral(L, "unknown");
    }
    return 1;
}