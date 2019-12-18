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
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_PLAYER_SELECT_EXCLUSIVE ; 
 int /*<<< orphan*/  assert (struct vlc_player_track const*) ; 
 struct vlc_player_track* vlc_player_GetTrackAt (int /*<<< orphan*/ *,int,size_t) ; 
 size_t vlc_player_GetTrackCount (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_SelectTrack (int /*<<< orphan*/ *,struct vlc_player_track const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_UnselectTrack (int /*<<< orphan*/ *,struct vlc_player_track const*) ; 

__attribute__((used)) static void
vlc_player_CycleTrack(vlc_player_t *player, enum es_format_category_e cat,
                      bool next)
{
    size_t count = vlc_player_GetTrackCount(player, cat);
    if (!count)
        return;

    size_t index;
    bool selected = false;
    for (size_t i = 0; i < count; ++i)
    {
        const struct vlc_player_track *track =
            vlc_player_GetTrackAt(player, cat, i);
        assert(track);
        if (track->selected)
        {
            if (selected)
            {
                /* Can't cycle through tracks if there are more than one
                 * selected */
                return;
            }
            index = i;
            selected = true;
        }
    }

    if (!selected)
    {
        /* No track selected: select the first or the last track */
        index = next ? 0 : count - 1;
        selected = true;
    }
    else
    {
        /* Unselect if we reach the end of the cycle */
        if ((next && index + 1 == count) || (!next && index == 0))
            selected = false;
        else /* Switch to the next or previous track */
            index = index + (next ? 1 : -1);
    }

    const struct vlc_player_track *track =
        vlc_player_GetTrackAt(player, cat, index);
    if (selected)
        vlc_player_SelectTrack(player, track, VLC_PLAYER_SELECT_EXCLUSIVE);
    else
        vlc_player_UnselectTrack(player, track);
}