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
struct TYPE_3__ {int /*<<< orphan*/  player; int /*<<< orphan*/  player_listener; } ;
typedef  TYPE_1__ vlc_playlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_player_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_RemoveListener (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ ) ; 

void
vlc_playlist_PlayerDestroy(vlc_playlist_t *playlist)
{
    vlc_player_Lock(playlist->player);
    vlc_player_RemoveListener(playlist->player, playlist->player_listener);
    vlc_player_Unlock(playlist->player);

    vlc_player_Delete(playlist->player);
}