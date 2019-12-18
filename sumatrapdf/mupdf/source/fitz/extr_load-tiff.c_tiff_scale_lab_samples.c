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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static void
tiff_scale_lab_samples(fz_context *ctx, unsigned char *buf, int bps, int n)
{
	int i;
	if (bps == 8)
		for (i = 0; i < n; i++, buf += 3)
		{
			buf[1] ^= 128;
			buf[2] ^= 128;
		}
	else if (bps == 16)
		for (i = 0; i < n; i++, buf += 6)
		{
			buf[2] ^= 128;
			buf[4] ^= 128;
		}
}