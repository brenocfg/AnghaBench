#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct TYPE_8__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_3__ libvlc_media_player_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_id; int /*<<< orphan*/  i_type; } ;
struct TYPE_6__ {TYPE_2__ media_player_es_changed; } ;
struct TYPE_9__ {TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ libvlc_event_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaPlayerESSelected ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  track_type_from_cat (int) ; 
 int vlc_es_id_GetCat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_es_id_GetInputId (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
on_track_selection_changed(vlc_player_t *player, vlc_es_id_t *unselected_id,
                           vlc_es_id_t *selected_id, void *data)
{
    (void) player;
    (void) unselected_id;

    libvlc_media_player_t *mp = data;

    libvlc_event_t event;
    event.type = libvlc_MediaPlayerESSelected;

    if (selected_id)
    {
        enum es_format_category_e cat = vlc_es_id_GetCat(selected_id);
        event.u.media_player_es_changed.i_type = track_type_from_cat(cat);
        event.u.media_player_es_changed.i_id =
            vlc_es_id_GetInputId(selected_id);
        libvlc_event_send(&mp->event_manager, &event);
    }
}