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
typedef  int /*<<< orphan*/ * vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_GetCurrentMedia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_NotifyMediaUpdated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
on_player_media_length_changed(vlc_player_t *player, vlc_tick_t new_length,
                               void *userdata)
{
    VLC_UNUSED(player);
    VLC_UNUSED(new_length);
    vlc_playlist_t *playlist = userdata;

    /* the playlist and the player share the lock */
    vlc_playlist_AssertLocked(playlist);

    input_item_t *media = vlc_player_GetCurrentMedia(player);
    assert(media);

    vlc_playlist_NotifyMediaUpdated(playlist, media);
}