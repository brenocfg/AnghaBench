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
struct info {unsigned char* mask; unsigned int height; unsigned int width; int /*<<< orphan*/  pix; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 unsigned char* fz_pixmap_samples (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gif_mask_transparency(fz_context *ctx, struct info *info)
{
	unsigned char *mp = info->mask;
	unsigned char *dp = fz_pixmap_samples(ctx, info->pix);
	unsigned int x, y;

	for (y = 0; y < info->height; y++)
		for (x = 0; x < info->width; x++, mp++, dp += 4)
			if (*mp == 0x00)
				dp[3] = 0;
}