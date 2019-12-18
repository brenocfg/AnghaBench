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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ vlc_playlist_listener_id ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (int /*<<< orphan*/ *) ; 

void
vlc_playlist_RemoveListener(vlc_playlist_t *playlist,
                            vlc_playlist_listener_id *listener)
{
    /* The playlist head is not needed to remove a node, but the list must be
     * locked. */
    vlc_playlist_AssertLocked(playlist); VLC_UNUSED(playlist);

    vlc_list_remove(&listener->node);
    free(listener);
}