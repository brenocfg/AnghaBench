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

__attribute__((used)) static int
line_is_blank(unsigned char *dst, const unsigned char *sp, int w)
{
	int zero = 0;

	while (w-- > 0)
	{
		zero |= (*dst++ = *sp++);
		zero |= (*dst++ = *sp++);
		zero |= (*dst++ = *sp++);
	}

	return zero == 0;
}