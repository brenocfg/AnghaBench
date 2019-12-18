#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_cat; } ;
struct vlc_player_track {int /*<<< orphan*/  es_id; TYPE_1__ fmt; } ;
struct TYPE_10__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_4__ libvlc_media_player_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_id; int /*<<< orphan*/  i_type; } ;
struct TYPE_9__ {TYPE_2__ media_player_es_changed; } ;
struct TYPE_11__ {TYPE_3__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ libvlc_event_t ;
typedef  enum vlc_player_list_action { ____Placeholder_vlc_player_list_action } vlc_player_list_action ;

/* Variables and functions */
 int VLC_PLAYER_LIST_ADDED ; 
 int VLC_PLAYER_LIST_REMOVED ; 
 int /*<<< orphan*/  libvlc_MediaPlayerESAdded ; 
 int /*<<< orphan*/  libvlc_MediaPlayerESDeleted ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  track_type_from_cat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_es_id_GetInputId (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_track_list_changed(vlc_player_t *player, enum vlc_player_list_action action,
                      const struct vlc_player_track *track, void *data)
{
    (void) player;

    libvlc_media_player_t *mp = data;

    libvlc_event_t event;
    if (action == VLC_PLAYER_LIST_ADDED)
        event.type = libvlc_MediaPlayerESAdded;
    else if (action == VLC_PLAYER_LIST_REMOVED)
        event.type = libvlc_MediaPlayerESDeleted;
    else
        /* no event to forward */
        return;

    event.u.media_player_es_changed.i_type =
        track_type_from_cat(track->fmt.i_cat);
    event.u.media_player_es_changed.i_id = vlc_es_id_GetInputId(track->es_id);

    libvlc_event_send(&mp->event_manager, &event);
}