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
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_7__ {float soft_gain; int soft_mute; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 scalar_t__ aout_GainRequest (TYPE_1__*,float) ; 
 int /*<<< orphan*/  aout_MuteReport (TYPE_1__*,int) ; 

__attribute__((used)) static int aout_SoftMuteSet (audio_output_t *aout, bool mute)
{
    aout_sys_t *sys = aout->sys;

    if (aout_GainRequest(aout, mute ? 0.f : sys->soft_gain))
        return -1;
    sys->soft_mute = mute;

    aout_MuteReport(aout, mute);
    return 0;
}