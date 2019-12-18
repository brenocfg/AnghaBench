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
typedef  int /*<<< orphan*/  libvlc_media_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_mi; int /*<<< orphan*/  p_mlist; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_list_path_of_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_play (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  set_current_playing_item (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 

int libvlc_media_list_player_play_item(libvlc_media_list_player_t * p_mlp, libvlc_media_t * p_md)
{
    lock(p_mlp);
    libvlc_media_list_path_t path = libvlc_media_list_path_of_item(p_mlp->p_mlist, p_md);
    if (!path)
    {
        libvlc_printerr("Item not found in media list");
        unlock(p_mlp);
        return -1;
    }

    set_current_playing_item(p_mlp, path);
    libvlc_media_player_play(p_mlp->p_mi);
    unlock(p_mlp);
    return 0;
}