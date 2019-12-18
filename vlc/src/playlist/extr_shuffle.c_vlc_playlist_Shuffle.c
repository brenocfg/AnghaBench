#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xsubi ;
struct TYPE_11__ {int size; int /*<<< orphan*/ ** data; } ;
struct TYPE_12__ {int current; TYPE_1__ items; int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; } ;
typedef  TYPE_2__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct vlc_playlist_state {int dummy; } ;

/* Variables and functions */
 size_t nrand48 (unsigned short*) ; 
 int /*<<< orphan*/  on_items_reset ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_2__*) ; 
 size_t vlc_playlist_IndexOf (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Notify (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_2__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_2__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_rand_bytes (unsigned short*,int) ; 

void
vlc_playlist_Shuffle(vlc_playlist_t *playlist)
{
    vlc_playlist_AssertLocked(playlist);
    if (playlist->items.size < 2)
        /* we use size_t (unsigned), so the following loop would be incorrect */
        return;

    vlc_playlist_item_t *current = playlist->current != -1
                                 ? playlist->items.data[playlist->current]
                                 : NULL;

    /* initialize separately instead of using vlc_lrand48() to avoid locking the
     * mutex once for each item */
    unsigned short xsubi[3];
    vlc_rand_bytes(xsubi, sizeof(xsubi));

    /* Fisher-Yates shuffle */
    for (size_t i = playlist->items.size - 1; i != 0; --i)
    {
        size_t selected = (size_t) (nrand48(xsubi) % (i + 1));

        /* swap items i and selected */
        vlc_playlist_item_t *tmp = playlist->items.data[i];
        playlist->items.data[i] = playlist->items.data[selected];
        playlist->items.data[selected] = tmp;
    }

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
}