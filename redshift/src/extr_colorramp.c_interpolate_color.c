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

__attribute__((used)) static void
interpolate_color(float a, const float *c1, const float *c2, float *c)
{
	c[0] = (1.0-a)*c1[0] + a*c2[0];
	c[1] = (1.0-a)*c1[1] + a*c2[1];
	c[2] = (1.0-a)*c1[2] + a*c2[2];
}