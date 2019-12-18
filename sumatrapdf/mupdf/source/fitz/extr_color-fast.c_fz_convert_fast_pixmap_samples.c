#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {TYPE_2__* colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_36__ {int type; } ;
typedef  TYPE_2__ fz_colorspace ;

/* Variables and functions */
 int FZ_COLORSPACE_BGR ; 
 int FZ_COLORSPACE_CMYK ; 
 int FZ_COLORSPACE_GRAY ; 
 int FZ_COLORSPACE_RGB ; 
 int /*<<< orphan*/  fast_bgr_to_cmyk (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_bgr_to_gray (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_cmyk_to_bgr (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_cmyk_to_cmyk (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_cmyk_to_gray (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_cmyk_to_rgb (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_gray_to_cmyk (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_gray_to_gray (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_gray_to_rgb (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_rgb_to_bgr (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_rgb_to_cmyk (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_rgb_to_gray (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fast_rgb_to_rgb (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fz_convert_slow_pixmap_samples (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/  fz_fast_any_to_alpha (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int) ; 

void
fz_convert_fast_pixmap_samples(fz_context *ctx, fz_pixmap *src, fz_pixmap *dst, int copy_spots)
{
	fz_colorspace *ss = src->colorspace;
	fz_colorspace *ds = dst->colorspace;
	int dtype = ds ? ds->type : FZ_COLORSPACE_GRAY;
	int stype = ss ? ss->type : FZ_COLORSPACE_GRAY;

	if (!ds)
	{
		fz_fast_any_to_alpha(ctx, src, dst, copy_spots);
	}

	else if (stype == FZ_COLORSPACE_GRAY)
	{
		if (dtype == FZ_COLORSPACE_GRAY)
			fast_gray_to_gray(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_RGB)
			fast_gray_to_rgb(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_BGR)
			fast_gray_to_rgb(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_CMYK)
			fast_gray_to_cmyk(ctx, src, dst, copy_spots);
		else
			goto slow;
	}

	else if (stype == FZ_COLORSPACE_RGB)
	{
		if (dtype == FZ_COLORSPACE_GRAY)
			fast_rgb_to_gray(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_RGB)
			fast_rgb_to_rgb(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_BGR)
			fast_rgb_to_bgr(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_CMYK)
			fast_rgb_to_cmyk(ctx, src, dst, copy_spots);
		else
			goto slow;
	}

	else if (stype == FZ_COLORSPACE_BGR)
	{
		if (dtype == FZ_COLORSPACE_GRAY)
			fast_bgr_to_gray(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_RGB)
			fast_rgb_to_bgr(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_BGR)
			fast_rgb_to_rgb(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_CMYK)
			fast_bgr_to_cmyk(ctx, src, dst, copy_spots);
		else
			goto slow;
	}

	else if (stype == FZ_COLORSPACE_CMYK)
	{
		if (dtype == FZ_COLORSPACE_GRAY)
			fast_cmyk_to_gray(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_RGB)
			fast_cmyk_to_rgb(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_BGR)
			fast_cmyk_to_bgr(ctx, src, dst, copy_spots);
		else if (dtype == FZ_COLORSPACE_CMYK)
			fast_cmyk_to_cmyk(ctx, src, dst, copy_spots);
		else
			goto slow;
	}
	else
	{
		goto slow;
	}
	return;

slow:
	fz_convert_slow_pixmap_samples(ctx, src, dst, NULL, fz_default_color_params, copy_spots);
}