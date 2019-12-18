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
struct TYPE_6__ {int /*<<< orphan*/  p_mi; int /*<<< orphan*/  current_playing_item_path; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_player_play (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  set_relative_playlist_position_and_play (TYPE_1__*,int) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 

void libvlc_media_list_player_play(libvlc_media_list_player_t * p_mlp)
{
    lock(p_mlp);
    if (!p_mlp->current_playing_item_path)
    {
        set_relative_playlist_position_and_play(p_mlp, 1);
        unlock(p_mlp);
        return; /* Will set to play */
    }
    libvlc_media_player_play(p_mlp->p_mi);
    unlock(p_mlp);
}