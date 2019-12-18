#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t size; int /*<<< orphan*/ ** data; } ;
struct TYPE_8__ {scalar_t__ order; int /*<<< orphan*/  randomizer; TYPE_1__ items; } ;
typedef  TYPE_2__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  randomizer_Select (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_SetCurrentIndex (TYPE_2__*,int) ; 
 int vlc_playlist_SetCurrentMedia (TYPE_2__*,int) ; 

int
vlc_playlist_GoTo(vlc_playlist_t *playlist, ssize_t index)
{
    vlc_playlist_AssertLocked(playlist);
    assert(index == -1 || (size_t) index < playlist->items.size);

    int ret = vlc_playlist_SetCurrentMedia(playlist, index);
    if (ret != VLC_SUCCESS)
        return ret;

    if (index != -1 && playlist->order == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM)
    {
        vlc_playlist_item_t *item = playlist->items.data[index];
        randomizer_Select(&playlist->randomizer, item);
    }

    vlc_playlist_SetCurrentIndex(playlist, index);
    return VLC_SUCCESS;
}