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
typedef  int /*<<< orphan*/  lua_State ;
typedef  enum vlc_playlist_playback_order { ____Placeholder_vlc_playlist_playback_order } vlc_playlist_playback_order ;

/* Variables and functions */
 int VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL ; 
 int VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int take_bool (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetPlaybackOrder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackOrder (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_random(lua_State *L)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);
    int top = lua_gettop(L);
    if (top > 1)
        return vlclua_error(L);

    vlc_playlist_Lock(playlist);

    bool enable;
    if (top == 0)
    {
        enum vlc_playlist_playback_order order =
                vlc_playlist_GetPlaybackOrder(playlist);
        enable = order != VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM;
    }
    else
    {
        /* use the provided value */
        enable = take_bool(L);
    }

    enum vlc_playlist_playback_order new_order = enable
                                    ? VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM
                                    : VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL;

    vlc_playlist_SetPlaybackOrder(playlist, new_order);

    vlc_playlist_Unlock(playlist);

    lua_pushboolean(L, enable);
    return 1;
}