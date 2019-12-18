#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  randomizer; int /*<<< orphan*/  listeners; } ;
typedef  TYPE_1__ vlc_playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  randomizer_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_ClearItems (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_PlayerDestroy (TYPE_1__*) ; 

void
vlc_playlist_Delete(vlc_playlist_t *playlist)
{
    assert(vlc_list_is_empty(&playlist->listeners));

    vlc_playlist_PlayerDestroy(playlist);
    randomizer_Destroy(&playlist->randomizer);
    vlc_playlist_ClearItems(playlist);
    free(playlist);
}