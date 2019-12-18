#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__** data; } ;
struct TYPE_14__ {scalar_t__ order; scalar_t__ current; TYPE_1__ items; int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  randomizer; } ;
typedef  TYPE_2__ vlc_playlist_t ;
struct TYPE_15__ {int /*<<< orphan*/  media; } ;
typedef  TYPE_3__ vlc_playlist_item_t ;
struct vlc_playlist_state {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int /*<<< orphan*/  on_items_added ; 
 int /*<<< orphan*/  randomizer_Add (int /*<<< orphan*/ *,TYPE_3__**,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_AutoPreparse (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_Notify (TYPE_2__*,int /*<<< orphan*/ ,size_t,TYPE_3__**,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_2__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_2__*,struct vlc_playlist_state*) ; 

__attribute__((used)) static void
vlc_playlist_ItemsInserted(vlc_playlist_t *playlist, size_t index, size_t count)
{
    if (playlist->order == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM)
        randomizer_Add(&playlist->randomizer,
                       &playlist->items.data[index], count);

    struct vlc_playlist_state state;
    vlc_playlist_state_Save(playlist, &state);

    if (playlist->current >= (ssize_t) index)
        playlist->current += count;
    playlist->has_prev = vlc_playlist_ComputeHasPrev(playlist);
    playlist->has_next = vlc_playlist_ComputeHasNext(playlist);

    vlc_playlist_item_t **items = &playlist->items.data[index];
    vlc_playlist_Notify(playlist, on_items_added, index, items, count);
    vlc_playlist_state_NotifyChanges(playlist, &state);

    for (size_t i = index; i < index + count; ++i)
    {
        vlc_playlist_item_t *item = playlist->items.data[i];
        vlc_playlist_AutoPreparse(playlist, item->media);
    }
}