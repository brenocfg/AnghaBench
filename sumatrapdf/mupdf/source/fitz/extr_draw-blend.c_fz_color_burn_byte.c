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

__attribute__((used)) static inline int fz_color_burn_byte(int b, int s)
{
	b = 255 - b;
	if (b <= 0)
		return 255;
	else if (b >= s)
		return 0;
	else
		return 0xff - (0x1fe * b + s) / (s << 1);
}