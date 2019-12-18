#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ current; scalar_t__ has_prev; scalar_t__ has_next; } ;
typedef  TYPE_1__ vlc_playlist_t ;
struct vlc_playlist_state {scalar_t__ current; scalar_t__ has_prev; scalar_t__ has_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  on_current_index_changed ; 
 int /*<<< orphan*/  on_has_next_changed ; 
 int /*<<< orphan*/  on_has_prev_changed ; 
 int /*<<< orphan*/  vlc_playlist_Notify (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void
vlc_playlist_state_NotifyChanges(vlc_playlist_t *playlist,
                                 struct vlc_playlist_state *saved_state)
{
    if (saved_state->current != playlist->current)
        vlc_playlist_Notify(playlist, on_current_index_changed, playlist->current);
    if (saved_state->has_prev != playlist->has_prev)
        vlc_playlist_Notify(playlist, on_has_prev_changed, playlist->has_prev);
    if (saved_state->has_next != playlist->has_next)
        vlc_playlist_Notify(playlist, on_has_next_changed, playlist->has_next);
}