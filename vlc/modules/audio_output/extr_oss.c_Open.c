#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int /*<<< orphan*/  device_select; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_9__ {int fd; int /*<<< orphan*/  device; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceSelect ; 
 int /*<<< orphan*/  DevicesEnum (TYPE_1__*) ; 
 int /*<<< orphan*/  Start ; 
 int /*<<< orphan*/  Stop ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_DeviceReport (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_SoftVolumeInit (TYPE_1__*) ; 
 TYPE_2__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritString (TYPE_1__*,char*) ; 

__attribute__((used)) static int Open (vlc_object_t *obj)
{
    audio_output_t *aout = (audio_output_t *)obj;

    aout_sys_t *sys = malloc (sizeof (*sys));
    if(unlikely( sys == NULL ))
        return VLC_ENOMEM;

    sys->fd = -1;
    sys->device = var_InheritString (aout, "oss-audio-device");

    aout->sys = sys;
    aout->start = Start;
    aout->stop = Stop;
    aout->device_select = DeviceSelect;
    aout_DeviceReport (aout, sys->device);
    aout_SoftVolumeInit (aout);

    DevicesEnum (aout);
    return VLC_SUCCESS;
}