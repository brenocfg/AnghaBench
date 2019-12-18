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
typedef  int int64_t ;

/* Variables and functions */

int64_t
lcompat_pow(int64_t x, int64_t y)
{
	int64_t result = 1;
	if (y < 0)
		return (0);

	while (y) {
		if (y & 1)
			result *= x;
		y >>= 1;
		x *= x;
	}
	return (result);
}