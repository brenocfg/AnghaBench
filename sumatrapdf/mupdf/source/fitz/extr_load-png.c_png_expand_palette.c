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
struct info {unsigned int height; unsigned int width; int /*<<< orphan*/ * palette; scalar_t__ transparency; int /*<<< orphan*/  cs; } ;
struct TYPE_6__ {int w; unsigned char* samples; int stride; int n; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* fz_new_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static fz_pixmap *
png_expand_palette(fz_context *ctx, struct info *info, fz_pixmap *src)
{
	fz_pixmap *dst = fz_new_pixmap(ctx, info->cs, src->w, src->h, NULL, info->transparency);
	unsigned char *sp = src->samples;
	unsigned char *dp = dst->samples;
	unsigned int x, y;
	int dstride = dst->stride - dst->w * dst->n;
	int sstride = src->stride - src->w * src->n;

	dst->xres = src->xres;
	dst->yres = src->yres;

	for (y = info->height; y > 0; y--)
	{
		for (x = info->width; x > 0; x--)
		{
			int v = *sp << 2;
			*dp++ = info->palette[v];
			*dp++ = info->palette[v + 1];
			*dp++ = info->palette[v + 2];
			if (info->transparency)
				*dp++ = info->palette[v + 3];
			++sp;
		}
		sp += sstride;
		dp += dstride;
	}

	fz_drop_pixmap(ctx, src);
	return dst;
}