#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  device_select; int /*<<< orphan*/  flush; int /*<<< orphan*/  pause; int /*<<< orphan*/  play; int /*<<< orphan*/  mute_set; int /*<<< orphan*/  volume_set; int /*<<< orphan*/  time_get; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_7__ {int /*<<< orphan*/ * client; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceSelect ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  MuteSet ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  Play ; 
 int /*<<< orphan*/  Start ; 
 int /*<<< orphan*/  Stop ; 
 int /*<<< orphan*/  TimeGet ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VolumeSet ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * var_CreateGetAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_object_parent (TYPE_1__*) ; 

__attribute__((used)) static int Open(vlc_object_t *obj)
{
    audio_output_t *aout = (audio_output_t *)obj;

    aout_sys_t *sys = malloc(sizeof (*sys));
    if (unlikely(sys == NULL))
        return VLC_ENOMEM;

    aout->sys = sys;
    sys->stream = NULL;
    sys->client = var_CreateGetAddress( vlc_object_parent(aout), "winstore-client" );
    if (sys->client != NULL)
        msg_Dbg( aout, "Reusing previous client: %p", sys->client );
    aout->start = Start;
    aout->stop = Stop;
    aout->time_get = TimeGet;
    aout->volume_set = VolumeSet;
    aout->mute_set = MuteSet;
    aout->play = Play;
    aout->pause = Pause;
    aout->flush = Flush;
    aout->device_select = DeviceSelect;
    return VLC_SUCCESS;
}