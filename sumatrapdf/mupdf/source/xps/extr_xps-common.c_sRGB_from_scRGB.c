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
 float pow (float,int) ; 

__attribute__((used)) static float sRGB_from_scRGB(float x)
{
	if (x < 0.0031308f)
		return 12.92f * x;
	return 1.055f * pow(x, 1/2.4f) - 0.055f;
}