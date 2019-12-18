#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct aout_sys {scalar_t__ length; int /*<<< orphan*/  first_play_date; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mute_set; int /*<<< orphan*/ * volume_set; int /*<<< orphan*/  stop; int /*<<< orphan*/  flush; int /*<<< orphan*/  pause; int /*<<< orphan*/  play; int /*<<< orphan*/  time_get; int /*<<< orphan*/  start; struct aout_sys* sys; } ;
typedef  TYPE_1__ audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  Play ; 
 int /*<<< orphan*/  Start ; 
 int /*<<< orphan*/  Stop ; 
 int /*<<< orphan*/  TimeGet ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 struct aout_sys* malloc (int) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    audio_output_t *aout = (audio_output_t *)obj;

    struct aout_sys *sys = aout->sys = malloc(sizeof(*sys));
    if (!sys)
        return VLC_ENOMEM;
    sys->first_play_date = VLC_TICK_INVALID;
    sys->length = 0;

    aout->start = Start;
    aout->time_get = TimeGet;
    aout->play = Play;
    aout->pause = Pause;
    aout->flush = Flush;
    aout->stop = Stop;
    aout->volume_set = NULL;
    aout->mute_set = NULL;
    return VLC_SUCCESS;
}