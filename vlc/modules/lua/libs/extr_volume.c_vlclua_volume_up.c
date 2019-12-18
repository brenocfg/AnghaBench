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
 int VLC_SUCCESS ; 
 long lroundf (float) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,long) ; 
 int vlc_player_aout_IncrementVolume (int /*<<< orphan*/ *,int,float*) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_volume_up(lua_State *L)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);
    vlc_player_t *player = vlc_playlist_GetPlayer(playlist);

    float volume;
    int steps = luaL_optinteger(L, 1, 1);
    int res = vlc_player_aout_IncrementVolume(player, steps, &volume);

    long i_volume = res == VLC_SUCCESS ? lroundf(volume * AOUT_VOLUME_DEFAULT)
                                       : 0;
    lua_pushnumber(L, i_volume);
    return 1;
}