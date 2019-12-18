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

/* Variables and functions */
 int M_PI ; 
 float modff (float,float*) ; 

__attribute__((used)) static float vlc_to_vdp_hue(float hue)
{
    float dummy;

    hue /= 360.f;
    hue = modff(hue, &dummy);
    if (hue > .5f)
        hue -= 1.f;
    return hue * (float)(2. * M_PI);
}