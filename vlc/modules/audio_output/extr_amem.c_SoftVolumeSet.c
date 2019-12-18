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
struct TYPE_6__ {float volume; int /*<<< orphan*/  mute; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 scalar_t__ aout_GainRequest (TYPE_1__*,float) ; 

__attribute__((used)) static int SoftVolumeSet (audio_output_t *aout, float vol)
{
    aout_sys_t *sys = aout->sys;

    vol = vol * vol * vol;
    if (!sys->mute && aout_GainRequest (aout, vol))
        return -1;
    sys->volume = vol;
    return 0;
}