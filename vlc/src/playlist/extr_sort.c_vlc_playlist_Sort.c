#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t size; int /*<<< orphan*/ ** data; } ;
struct TYPE_13__ {int current; TYPE_1__ items; int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; } ;
typedef  TYPE_2__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct vlc_playlist_state {int dummy; } ;
struct vlc_playlist_sort_criterion {int dummy; } ;
struct vlc_playlist_item_meta {int /*<<< orphan*/ * item; } ;
struct sort_request {size_t member_1; struct vlc_playlist_sort_criterion const* member_0; } ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compare_meta ; 
 int /*<<< orphan*/  on_items_reset ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_DeleteMetaArray (struct vlc_playlist_item_meta**,size_t) ; 
 size_t vlc_playlist_IndexOf (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct vlc_playlist_item_meta** vlc_playlist_NewMetaArray (TYPE_2__*,struct vlc_playlist_sort_criterion const*,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_Notify (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_2__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_2__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_qsort (struct vlc_playlist_item_meta**,size_t,int,int /*<<< orphan*/ ,struct sort_request*) ; 

int
vlc_playlist_Sort(vlc_playlist_t *playlist,
                  const struct vlc_playlist_sort_criterion criteria[],
                  size_t count)
{
    assert(count > 0);
    vlc_playlist_AssertLocked(playlist);

    vlc_playlist_item_t *current = playlist->current != -1
                                 ? playlist->items.data[playlist->current]
                                 : NULL;

    struct vlc_playlist_item_meta **array =
        vlc_playlist_NewMetaArray(playlist, criteria, count);
    if (unlikely(!array))
        return VLC_ENOMEM;

    struct sort_request req = { criteria, count };

    vlc_qsort(array, playlist->items.size, sizeof(*array), compare_meta, &req);

    /* apply the sorting result to the playlist */
    for (size_t i = 0; i < playlist->items.size; ++i)
        playlist->items.data[i] = array[i]->item;

    vlc_playlist_DeleteMetaArray(array, playlist->items.size);

    struct vlc_playlist_state state;
    if (current)
    {
        /* the current position have changed after the shuffle */
        vlc_playlist_state_Save(playlist, &state);
        playlist->current = vlc_playlist_IndexOf(playlist, current);
        playlist->has_prev = vlc_playlist_ComputeHasPrev(playlist);
        playlist->has_next = vlc_playlist_ComputeHasNext(playlist);
    }

    vlc_playlist_Notify(playlist, on_items_reset, playlist->items.data,
                        playlist->items.size);
    if (current)
        vlc_playlist_state_NotifyChanges(playlist, &state);

    return VLC_SUCCESS;
}