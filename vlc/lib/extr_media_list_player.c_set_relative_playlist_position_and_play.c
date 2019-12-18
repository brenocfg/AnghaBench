#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_t ;
struct TYPE_13__ {scalar_t__ e_playback_mode; int /*<<< orphan*/  event_manager; int /*<<< orphan*/  p_mlist; int /*<<< orphan*/  p_mi; int /*<<< orphan*/  current_playing_item_path; } ;
typedef  TYPE_3__ libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_path_t ;
struct TYPE_11__ {int /*<<< orphan*/ * item; } ;
struct TYPE_12__ {TYPE_1__ media_list_player_next_item_set; } ;
struct TYPE_14__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ libvlc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (TYPE_3__*) ; 
 int /*<<< orphan*/  get_next_path (TYPE_3__*,int) ; 
 int /*<<< orphan*/  get_previous_path (TYPE_3__*,int) ; 
 int /*<<< orphan*/  libvlc_MediaListPlayerNextItemSet ; 
 int /*<<< orphan*/  libvlc_MediaListPlayerPlayed ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * libvlc_media_list_item_at_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_list_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_list_path_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_list_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_player_play (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 scalar_t__ libvlc_playback_mode_loop ; 
 scalar_t__ libvlc_playback_mode_repeat ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  set_current_playing_item (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_relative_playlist_position_and_play(
                                      libvlc_media_list_player_t * p_mlp,
                                      int i_relative_position)
{
    assert_locked(p_mlp);

    if (!p_mlp->p_mlist)
    {
        libvlc_printerr("No media list");
        return -1;
    }

    libvlc_media_list_lock(p_mlp->p_mlist);

    libvlc_media_list_path_t path = p_mlp->current_playing_item_path;

    if(p_mlp->e_playback_mode != libvlc_playback_mode_repeat)
    {
        bool b_loop = (p_mlp->e_playback_mode == libvlc_playback_mode_loop);

        while (i_relative_position > 0)
        {
            path = get_next_path(p_mlp, b_loop);
            set_current_playing_item(p_mlp, path);
            --i_relative_position;
        }

        while (i_relative_position < 0)
        {
            path = get_previous_path(p_mlp, b_loop);
            set_current_playing_item(p_mlp, path);
            ++i_relative_position;
        }
    }
    else
    {
        set_current_playing_item(p_mlp, path);
    }

#ifdef DEBUG_MEDIA_LIST_PLAYER
    printf("Playing:");
    libvlc_media_list_path_dump(path);
#endif

    if (!path)
    {
        libvlc_media_list_unlock(p_mlp->p_mlist);
        /* Send list played event */
        libvlc_event_t event;
        event.type = libvlc_MediaListPlayerPlayed;
        libvlc_event_send(&p_mlp->event_manager, &event);
        return -1;
    }

    libvlc_media_player_play(p_mlp->p_mi);

    libvlc_media_list_unlock(p_mlp->p_mlist);

    /* Send the next item event */
    libvlc_event_t event;
    event.type = libvlc_MediaListPlayerNextItemSet;
    libvlc_media_t * p_md = libvlc_media_list_item_at_path(p_mlp->p_mlist, path);
    event.u.media_list_player_next_item_set.item = p_md;
    libvlc_event_send(&p_mlp->event_manager, &event);
    libvlc_media_release(p_md);
    return 0;
}