#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ vlc_playlist_t ;
struct vlc_playlist_state {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_1__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_1__*,struct vlc_playlist_state*) ; 

__attribute__((used)) static void
vlc_playlist_SetCurrentIndex(vlc_playlist_t *playlist, ssize_t index)
{
    struct vlc_playlist_state state;
    vlc_playlist_state_Save(playlist, &state);

    playlist->current = index;
    playlist->has_prev = vlc_playlist_ComputeHasPrev(playlist);
    playlist->has_next = vlc_playlist_ComputeHasNext(playlist);

    vlc_playlist_state_NotifyChanges(playlist, &state);
}