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
 scalar_t__ AOUT_VOLUME_DEFAULT ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int vlc_player_aout_SetVolume (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_playlist_internal (int /*<<< orphan*/ *) ; 
 int vlclua_push_ret (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_volume_set(lua_State *L)
{
    vlc_playlist_t *playlist = vlclua_get_playlist_internal(L);
    vlc_player_t *player = vlc_playlist_GetPlayer(playlist);

    int i_volume = luaL_checkinteger(L, 1);
    if (i_volume < 0)
        i_volume = 0;

    float volume = i_volume / (float) AOUT_VOLUME_DEFAULT;
    int ret = vlc_player_aout_SetVolume(player, volume);
    return vlclua_push_ret(L, ret);
}