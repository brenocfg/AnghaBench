#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct playlist_state {int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  current; int /*<<< orphan*/  playlist_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_HasNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_HasPrev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
playlist_state_init(struct playlist_state *state, vlc_playlist_t *playlist)
{
    state->playlist_size = vlc_playlist_Count(playlist);
    state->current = vlc_playlist_GetCurrentIndex(playlist);
    state->has_prev = vlc_playlist_HasPrev(playlist);
    state->has_next = vlc_playlist_HasNext(playlist);
}