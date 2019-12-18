#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_t ;
struct TYPE_12__ {int /*<<< orphan*/  event_manager; int /*<<< orphan*/  p_mi; } ;
typedef  TYPE_3__ libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_path_t ;
struct TYPE_10__ {int /*<<< orphan*/ * item; } ;
struct TYPE_11__ {TYPE_1__ media_list_player_next_item_set; } ;
struct TYPE_13__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ libvlc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaListPlayerNextItemSet ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  libvlc_media_list_path_with_root_index (int) ; 
 int /*<<< orphan*/ * libvlc_media_player_get_media (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_player_play (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (TYPE_3__*) ; 
 int /*<<< orphan*/  set_current_playing_item (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock (TYPE_3__*) ; 

int libvlc_media_list_player_play_item_at_index(libvlc_media_list_player_t * p_mlp, int i_index)
{
    lock(p_mlp);
    libvlc_media_list_path_t path = libvlc_media_list_path_with_root_index(i_index);
    set_current_playing_item(p_mlp, path);
    libvlc_media_t *p_md = libvlc_media_player_get_media(p_mlp->p_mi);
    libvlc_media_player_play(p_mlp->p_mi);
    unlock(p_mlp);

    if (!p_md)
        return -1;

    /* Send the next item event */
    libvlc_event_t event;
    event.type = libvlc_MediaListPlayerNextItemSet;
    event.u.media_list_player_next_item_set.item = p_md;
    libvlc_event_send(&p_mlp->event_manager, &event);
    libvlc_media_release(p_md);
    return 0;
}