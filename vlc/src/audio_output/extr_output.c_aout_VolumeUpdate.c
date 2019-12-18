#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 scalar_t__ AOUT_VOLUME_DEFAULT ; 
 float aout_VolumeGet (int /*<<< orphan*/ *) ; 
 int aout_VolumeSet (int /*<<< orphan*/ *,float) ; 
 float roundf (float) ; 
 float var_InheritFloat (int /*<<< orphan*/ *,char*) ; 

int aout_VolumeUpdate (audio_output_t *aout, int value, float *volp)
{
    int ret = -1;
    float stepSize = var_InheritFloat (aout, "volume-step") / (float)AOUT_VOLUME_DEFAULT;
    float delta = value * stepSize;
    float vol = aout_VolumeGet (aout);

    if (vol >= 0.f)
    {
        vol += delta;
        if (vol < 0.f)
            vol = 0.f;
        if (vol > 2.f)
            vol = 2.f;
        vol = (roundf (vol / stepSize)) * stepSize;
        if (volp != NULL)
            *volp = vol;
        ret = aout_VolumeSet (aout, vol);
    }
    return ret;
}