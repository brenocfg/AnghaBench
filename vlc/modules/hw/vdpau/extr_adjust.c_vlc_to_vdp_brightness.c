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

__attribute__((used)) static float vlc_to_vdp_brightness(float brightness)
{
    brightness -= 1.f;
    if (brightness > +1.f)
        brightness = +1.f;
    if (brightness < -1.f)
        brightness = -1.f;
    return brightness;
}