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
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {unsigned int volume; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 scalar_t__ SIO_MAXVOL ; 
 int /*<<< orphan*/  aout_MuteReport (TYPE_1__*,int) ; 
 int /*<<< orphan*/  aout_VolumeReport (TYPE_1__*,float) ; 

__attribute__((used)) static void VolumeChanged (void *arg, unsigned volume)
{
    audio_output_t *aout = arg;
    aout_sys_t *p_sys = aout->sys;
    float fvol = (float)volume / (float)SIO_MAXVOL;

    aout_VolumeReport (aout, fvol);
    aout_MuteReport (aout, volume == 0);
    if (volume) /* remember last non-zero volume to unmute later */
        p_sys->volume = volume;
}