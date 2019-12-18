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
fz_unpack_line_with_padding(unsigned char *dp, unsigned char *sp, int w, int n)
{
	int x, k;

	for (x = 0; x < w; x++)
	{
		for (k = 0; k < n; k++)
			*dp++ = *sp++;
		*dp++ = 255;
	}
}