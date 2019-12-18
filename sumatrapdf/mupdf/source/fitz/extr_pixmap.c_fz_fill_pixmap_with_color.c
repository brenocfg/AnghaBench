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
struct TYPE_3__ {int alpha; int s; int w; int h; unsigned char* samples; int stride; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int FZ_MAX_COLORS ; 
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_convert_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
fz_fill_pixmap_with_color(fz_context *ctx, fz_pixmap *pix, fz_colorspace *colorspace, float *color, fz_color_params color_params)
{
	float colorfv[FZ_MAX_COLORS];
	unsigned char colorbv[FZ_MAX_COLORS];
	int i, n, a, s, x, y, w, h;

	n = fz_colorspace_n(ctx, pix->colorspace);
	a = pix->alpha;
	s = pix->s;
	fz_convert_color(ctx, colorspace, color, pix->colorspace, colorfv, NULL, color_params);
	for (i = 0; i < n; ++i)
		colorbv[i] = colorfv[i] * 255;

	w = pix->w;
	h = pix->h;
	for (y = 0; y < h; ++y)
	{
		unsigned char *p = pix->samples + y * pix->stride;
		for (x = 0; x < w; ++x)
		{
			for (i = 0; i < n; ++i)
				*p++ = colorbv[i];
			for (i = 0; i < s; ++i)
				*p++ = 0;
			if (a)
				*p++ = 255;
		}
	}
}