#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ vlc_playlist_t ;
struct vlc_playlist_state {int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  current; } ;

/* Variables and functions */

void
vlc_playlist_state_Save(vlc_playlist_t *playlist,
                        struct vlc_playlist_state *state)
{
    state->current = playlist->current;
    state->has_prev = playlist->has_prev;
    state->has_next = playlist->has_next;
}