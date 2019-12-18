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

__attribute__((used)) static float vlc_to_vdp_contrast(float contrast)
{
    if (contrast > 10.f)
        contrast = 10.f;
    if (contrast < 0.f)
        contrast = 0.f;
    return contrast;
}