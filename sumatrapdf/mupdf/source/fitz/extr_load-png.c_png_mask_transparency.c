#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct info {int width; int n; int depth; unsigned int height; unsigned char* samples; scalar_t__* trns; } ;
struct TYPE_3__ {unsigned char* samples; unsigned int stride; unsigned int n; } ;
typedef  TYPE_1__ fz_pixmap ;

/* Variables and functions */
 scalar_t__ getcomp (unsigned char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
png_mask_transparency(struct info *info, fz_pixmap *dst)
{
	unsigned int stride = (info->width * info->n * info->depth + 7) / 8;
	unsigned int depth = info->depth;
	unsigned int n = info->n;
	unsigned int x, y, k, t;

	for (y = 0; y < info->height; y++)
	{
		unsigned char *sp = info->samples + (unsigned int)(y * stride);
		unsigned char *dp = dst->samples + (unsigned int)(y * dst->stride);
		for (x = 0; x < info->width; x++)
		{
			t = 1;
			for (k = 0; k < n; k++)
				if (getcomp(sp, x * n + k, depth) != info->trns[k])
					t = 0;
			if (t)
				dp[x * dst->n + dst->n - 1] = 0;
		}
	}
}