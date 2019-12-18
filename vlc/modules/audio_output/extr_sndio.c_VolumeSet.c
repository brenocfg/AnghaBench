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
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_5__ {unsigned int volume; int /*<<< orphan*/  hdl; int /*<<< orphan*/  mute; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 float SIO_MAXVOL ; 
 unsigned int lroundf (float) ; 
 int /*<<< orphan*/  sio_setvol (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int VolumeSet (audio_output_t *aout, float fvol)
{
    aout_sys_t *sys = aout->sys;
    unsigned volume;

    if (fvol < 0)
        fvol = 0;
    if (fvol > 1)
        fvol = 1;
    volume = lroundf (fvol * SIO_MAXVOL);
    if (!sys->mute && !sio_setvol (sys->hdl, volume))
        return -1;
    sys->volume = volume;
    return 0;
}