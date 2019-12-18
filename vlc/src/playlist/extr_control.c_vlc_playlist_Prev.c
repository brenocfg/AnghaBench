#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_10__ {scalar_t__ order; int /*<<< orphan*/  player; TYPE_1__ items; int /*<<< orphan*/  randomizer; } ;
typedef  TYPE_2__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 scalar_t__ VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * randomizer_Prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_osd_Message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_2__*) ; 
 int vlc_playlist_GetPrevIndex (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_SetCurrentIndex (TYPE_2__*,int) ; 
 int vlc_playlist_SetCurrentMedia (TYPE_2__*,int) ; 

int
vlc_playlist_Prev(vlc_playlist_t *playlist)
{
    vlc_playlist_AssertLocked(playlist);

    if (!vlc_playlist_ComputeHasPrev(playlist))
        return VLC_EGENERIC;

    ssize_t index = vlc_playlist_GetPrevIndex(playlist);
    assert(index != -1);

    int ret = vlc_playlist_SetCurrentMedia(playlist, index);
    if (ret != VLC_SUCCESS)
        return ret;

    if (playlist->order == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM)
    {
        /* mark the item as selected in the randomizer */
        vlc_playlist_item_t *selected = randomizer_Prev(&playlist->randomizer);
        assert(selected == playlist->items.data[index]);
        VLC_UNUSED(selected);
    }

    vlc_playlist_SetCurrentIndex(playlist, index);
    vlc_player_osd_Message(playlist->player, _("Previous"));
    return VLC_SUCCESS;
}