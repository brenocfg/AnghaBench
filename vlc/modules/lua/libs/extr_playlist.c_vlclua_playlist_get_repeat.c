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
typedef  enum vlc_playlist_playback_repeat { ____Placeholder_vlc_playlist_playback_repeat } vlc_playlist_playback_repeat ;

/* Variables and functions */
 int VLC_PLAYLIST_PLAYBACK_REPEAT_NONE ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int vlc_playlist_GetPlaybackRepeat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_get_repeat(lua_State *L)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);

    vlc_playlist_Lock(playlist);
    enum vlc_playlist_playback_repeat repeat =
            vlc_playlist_GetPlaybackRepeat(playlist);
    bool result = repeat != VLC_PLAYLIST_PLAYBACK_REPEAT_NONE;
    vlc_playlist_Unlock(playlist);

    lua_pushboolean(L, result);
    return 1;
}