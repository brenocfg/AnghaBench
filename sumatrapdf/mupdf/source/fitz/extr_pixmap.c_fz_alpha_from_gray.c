#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int n; unsigned char* samples; int stride; int h; int w; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_pixmap_bbox (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

fz_pixmap *
fz_alpha_from_gray(fz_context *ctx, fz_pixmap *gray)
{
	fz_pixmap *alpha;
	unsigned char *sp, *dp;
	int w, h, sstride, dstride;

	assert(gray->n == 1);

	alpha = fz_new_pixmap_with_bbox(ctx, NULL, fz_pixmap_bbox(ctx, gray), 0, 1);
	dp = alpha->samples;
	dstride = alpha->stride;
	sp = gray->samples;
	sstride = gray->stride;

	h = gray->h;
	w = gray->w;
	while (h--)
	{
		memcpy(dp, sp, w);
		sp += sstride;
		dp += dstride;
	}

	return alpha;
}