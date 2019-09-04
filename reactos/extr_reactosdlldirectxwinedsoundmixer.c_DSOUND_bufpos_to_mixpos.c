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
struct TYPE_5__ {TYPE_1__* pwfx; } ;
struct TYPE_4__ {int wBitsPerSample; } ;
typedef  TYPE_2__ DirectSoundDevice ;
typedef  int DWORD ;

/* Variables and functions */

DWORD DSOUND_bufpos_to_mixpos(const DirectSoundDevice* device, DWORD pos)
{
    DWORD ret = pos * 32 / device->pwfx->wBitsPerSample;
    if (device->pwfx->wBitsPerSample == 32)
        ret *= 2;
    return ret;
}