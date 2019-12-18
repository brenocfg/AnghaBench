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
struct TYPE_8__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_3__ libvlc_media_player_t ;
struct TYPE_6__ {float volume; } ;
struct TYPE_7__ {TYPE_1__ media_player_audio_volume; } ;
struct TYPE_9__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ libvlc_event_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_MediaPlayerAudioVolume ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void
on_volume_changed(audio_output_t *aout, float new_volume, void *data)
{
    (void) aout;

    libvlc_media_player_t *mp = data;

    libvlc_event_t event;
    event.type = libvlc_MediaPlayerAudioVolume;
    event.u.media_player_audio_volume.volume = new_volume;

    libvlc_event_send(&mp->event_manager, &event);
}