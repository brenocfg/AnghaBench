#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_4__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ libvlc_event_t ;
typedef  enum vlc_player_error { ____Placeholder_vlc_player_error } vlc_player_error ;

/* Variables and functions */
#define  VLC_PLAYER_ERROR_GENERIC 129 
#define  VLC_PLAYER_ERROR_NONE 128 
 int /*<<< orphan*/  libvlc_MediaPlayerEncounteredError ; 
 int /*<<< orphan*/  libvlc_MediaPlayerNothingSpecial ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void
on_error_changed(vlc_player_t *player, enum vlc_player_error error, void *data)
{
    (void) player;

    libvlc_media_player_t *mp = data;

    libvlc_event_t event;
    switch (error) {
        case VLC_PLAYER_ERROR_NONE:
            event.type = libvlc_MediaPlayerNothingSpecial;
            break;
        case VLC_PLAYER_ERROR_GENERIC:
            event.type = libvlc_MediaPlayerEncounteredError;
            break;
        default:
            vlc_assert_unreachable();
    }

    libvlc_event_send(&mp->event_manager, &event);
}