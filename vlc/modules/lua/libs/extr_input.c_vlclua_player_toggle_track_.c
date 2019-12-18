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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_track {scalar_t__ selected; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 struct vlc_player_track* FindTrack (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  VLC_PLAYER_SELECT_EXCLUSIVE ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SelectTrack (int /*<<< orphan*/ *,struct vlc_player_track const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_UnselectTrack (int /*<<< orphan*/ *,struct vlc_player_track const*) ; 
 int /*<<< orphan*/ * vlclua_get_player_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_player_toggle_track_(lua_State *L,
                                       enum es_format_category_e cat,
                                       int id)
{
    vlc_player_t *player = vlclua_get_player_internal(L);

    vlc_player_Lock(player);

    const struct vlc_player_track *track = FindTrack(player, cat, id);
    if (track) {
        if (track->selected)
            vlc_player_UnselectTrack(player, track);
        else
            vlc_player_SelectTrack(player, track, VLC_PLAYER_SELECT_EXCLUSIVE);
    }

    vlc_player_Unlock(player);

    return 0;
}