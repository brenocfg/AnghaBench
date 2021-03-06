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
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetNextMedia (int /*<<< orphan*/ *) ; 

__attribute__((used)) static input_item_t *
player_get_next_media(vlc_player_t *player, void *userdata)
{
    VLC_UNUSED(player);
    vlc_playlist_t *playlist = userdata;
    return vlc_playlist_GetNextMedia(playlist);
}