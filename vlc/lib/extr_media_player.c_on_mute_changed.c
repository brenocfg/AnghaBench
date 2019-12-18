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
struct TYPE_4__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ libvlc_event_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaPlayerMuted ; 
 int /*<<< orphan*/  libvlc_MediaPlayerUnmuted ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
on_mute_changed(audio_output_t *aout, bool new_muted, void *data)
{
    (void) aout;

    libvlc_media_player_t *mp = data;

    libvlc_event_t event;
    event.type = new_muted ? libvlc_MediaPlayerMuted
                           : libvlc_MediaPlayerUnmuted;

    libvlc_event_send(&mp->event_manager, &event);
}