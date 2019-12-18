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
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int take_bool (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetPlaybackRepeat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackRepeat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_playlist_repeat_(lua_State *L,
                               enum vlc_playlist_playback_repeat enabled_mode)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);
    int top = lua_gettop(L);
    if (top > 1)
        return vlclua_error(L);

    vlc_playlist_Lock(playlist);

    bool enable;
    if (top == 0)
    {
        /* no value provided, toggle the current */
        enum vlc_playlist_playback_repeat repeat =
                vlc_playlist_GetPlaybackRepeat(playlist);
        enable = repeat != enabled_mode;
    }
    else
    {
        /* use the provided value */
        enable = take_bool(L);
    }

    enum vlc_playlist_playback_repeat new_repeat = enable
                                    ? enabled_mode
                                    : VLC_PLAYLIST_PLAYBACK_REPEAT_NONE;

    vlc_playlist_SetPlaybackRepeat(playlist, new_repeat);

    vlc_playlist_Unlock(playlist);

    lua_pushboolean(L, enable);
    return 1;
}