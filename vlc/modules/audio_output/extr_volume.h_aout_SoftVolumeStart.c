#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_8__ {float soft_gain; scalar_t__ soft_mute; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 scalar_t__ aout_GainRequest (TYPE_1__*,float) ; 
 int /*<<< orphan*/  aout_MuteReport (TYPE_1__*,int) ; 
 int /*<<< orphan*/  aout_VolumeReport (TYPE_1__*,float) ; 

__attribute__((used)) static void aout_SoftVolumeStart (audio_output_t *aout)
{
    aout_sys_t *sys = aout->sys;

    if (aout_GainRequest(aout, sys->soft_mute ? 0.f : sys->soft_gain))
    {
        aout_MuteReport(aout, false);
        aout_VolumeReport(aout, 1.f);
    }
}