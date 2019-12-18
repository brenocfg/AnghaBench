#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int current; int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; } ;
typedef  TYPE_1__ vlc_playlist_t ;
struct vlc_playlist_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  on_items_moved ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_Notify (TYPE_1__*,int /*<<< orphan*/ ,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_1__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_1__*,struct vlc_playlist_state*) ; 

__attribute__((used)) static void
vlc_playlist_ItemsMoved(vlc_playlist_t *playlist, size_t index, size_t count,
                        size_t target)
{
    struct vlc_playlist_state state;
    vlc_playlist_state_Save(playlist, &state);

    if (playlist->current != -1) {
        size_t current = (size_t) playlist->current;
        if (index < target)
        {
            if (current >= index && current < index + count)
                /* current item belongs to the moved block */
                playlist->current += target - index;
            else if (current >= index + count && current < target + count)
                /* current item was shifted backwards to the moved block */
                playlist->current -= count;
            /* else the current item does not move */
        }
        else
        {
            if (current >= index && current < index + count)
                /* current item belongs to the moved block */
                playlist->current -= index - target;
            else if (current >= target && current < index)
                /* current item was shifted forward to the moved block */
                playlist->current += count;
            /* else the current item does not move */
        }
    }

    playlist->has_prev = vlc_playlist_ComputeHasPrev(playlist);
    playlist->has_next = vlc_playlist_ComputeHasNext(playlist);

    vlc_playlist_Notify(playlist, on_items_moved, index, count, target);
    vlc_playlist_state_NotifyChanges(playlist, &state);
}