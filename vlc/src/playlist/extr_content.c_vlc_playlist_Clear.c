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
struct TYPE_6__ {int /*<<< orphan*/  player; } ;
typedef  TYPE_1__ vlc_playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int vlc_player_SetCurrentMedia (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_ClearItems (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_ItemsReset (TYPE_1__*) ; 

void
vlc_playlist_Clear(vlc_playlist_t *playlist)
{
    vlc_playlist_AssertLocked(playlist);

    int ret = vlc_player_SetCurrentMedia(playlist->player, NULL);
    VLC_UNUSED(ret); /* what could we do? */

    vlc_playlist_ClearItems(playlist);
    vlc_playlist_ItemsReset(playlist);
}