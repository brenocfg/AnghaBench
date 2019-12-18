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
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {scalar_t__ order; int current; TYPE_1__ items; int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  randomizer; } ;
typedef  TYPE_2__ vlc_playlist_t ;
struct vlc_playlist_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int /*<<< orphan*/  on_items_reset ; 
 int /*<<< orphan*/  randomizer_Clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_Notify (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_2__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_2__*,struct vlc_playlist_state*) ; 

__attribute__((used)) static void
vlc_playlist_ItemsReset(vlc_playlist_t *playlist)
{
    if (playlist->order == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM)
        randomizer_Clear(&playlist->randomizer);

    struct vlc_playlist_state state;
    vlc_playlist_state_Save(playlist, &state);

    playlist->current = -1;
    playlist->has_prev = vlc_playlist_ComputeHasPrev(playlist);
    playlist->has_next = vlc_playlist_ComputeHasNext(playlist);

    vlc_playlist_Notify(playlist, on_items_reset, playlist->items.data,
                   playlist->items.size);
    vlc_playlist_state_NotifyChanges(playlist, &state);
}