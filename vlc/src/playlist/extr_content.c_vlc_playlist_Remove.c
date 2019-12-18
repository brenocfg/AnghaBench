#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t size; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int /*<<< orphan*/  player; int /*<<< orphan*/  current; TYPE_2__ items; } ;
typedef  TYPE_1__ vlc_playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_player_InvalidateNextMedia (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_1__*) ; 
 int vlc_playlist_ItemsRemoved (TYPE_1__*,size_t,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_ItemsRemoving (TYPE_1__*,size_t,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_SetCurrentMedia (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_item_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vector_remove_slice (TYPE_2__*,size_t,size_t) ; 

void
vlc_playlist_Remove(vlc_playlist_t *playlist, size_t index, size_t count)
{
    vlc_playlist_AssertLocked(playlist);
    assert(index < playlist->items.size);

    vlc_playlist_ItemsRemoving(playlist, index, count);

    for (size_t i = 0; i < count; ++i)
        vlc_playlist_item_Release(playlist->items.data[index + i]);

    vlc_vector_remove_slice(&playlist->items, index, count);

    bool current_media_changed = vlc_playlist_ItemsRemoved(playlist, index,
                                                           count);
    if (current_media_changed)
        vlc_playlist_SetCurrentMedia(playlist, playlist->current);
    else
        vlc_player_InvalidateNextMedia(playlist->player);
}