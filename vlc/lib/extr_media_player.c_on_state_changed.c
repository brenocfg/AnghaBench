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
typedef  enum vlc_player_state { ____Placeholder_vlc_player_state } vlc_player_state ;

/* Variables and functions */
#define  VLC_PLAYER_STATE_PAUSED 132 
#define  VLC_PLAYER_STATE_PLAYING 131 
#define  VLC_PLAYER_STATE_STARTED 130 
#define  VLC_PLAYER_STATE_STOPPED 129 
#define  VLC_PLAYER_STATE_STOPPING 128 
 int /*<<< orphan*/  libvlc_MediaPlayerEndReached ; 
 int /*<<< orphan*/  libvlc_MediaPlayerOpening ; 
 int /*<<< orphan*/  libvlc_MediaPlayerPaused ; 
 int /*<<< orphan*/  libvlc_MediaPlayerPlaying ; 
 int /*<<< orphan*/  libvlc_MediaPlayerStopped ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void
on_state_changed(vlc_player_t *player, enum vlc_player_state new_state,
                 void *data)
{
    (void) player;

    libvlc_media_player_t *mp = data;

    libvlc_event_t event;
    switch (new_state) {
        case VLC_PLAYER_STATE_STOPPED:
            event.type = libvlc_MediaPlayerStopped;
            break;
        case VLC_PLAYER_STATE_STOPPING:
            event.type = libvlc_MediaPlayerEndReached;
            break;
        case VLC_PLAYER_STATE_STARTED:
            event.type = libvlc_MediaPlayerOpening;
            break;
        case VLC_PLAYER_STATE_PLAYING:
            event.type = libvlc_MediaPlayerPlaying;
            break;
        case VLC_PLAYER_STATE_PAUSED:
            event.type = libvlc_MediaPlayerPaused;
            break;
        default:
            vlc_assert_unreachable();
    }

    libvlc_event_send(&mp->event_manager, &event);
}