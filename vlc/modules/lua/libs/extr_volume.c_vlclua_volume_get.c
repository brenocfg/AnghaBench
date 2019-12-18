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
 float AOUT_VOLUME_DEFAULT ; 
 long lroundf (float) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,long) ; 
 float vlc_player_aout_GetVolume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_volume_get(lua_State *L)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);
    vlc_player_t *player = vlc_playlist_GetPlayer(playlist);

    float volume = vlc_player_aout_GetVolume(player);

    long i_volume = lroundf(volume * AOUT_VOLUME_DEFAULT);
    lua_pushnumber(L, i_volume);
    return 1;
}