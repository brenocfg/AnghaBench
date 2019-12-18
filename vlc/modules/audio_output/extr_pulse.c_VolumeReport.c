#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pa_volume_t ;
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {int /*<<< orphan*/  cvolume; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 float PA_VOLUME_NORM ; 
 int /*<<< orphan*/  aout_VolumeReport (TYPE_1__*,float) ; 
 scalar_t__ pa_cvolume_max (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void VolumeReport(audio_output_t *aout)
{
    aout_sys_t *sys = aout->sys;
    pa_volume_t volume = pa_cvolume_max(&sys->cvolume);

    aout_VolumeReport(aout, (float)volume / PA_VOLUME_NORM);
}