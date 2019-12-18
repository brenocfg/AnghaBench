#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_convert_fn ;

/* Variables and functions */
 int FZ_COLORSPACE_BGR ; 
 int FZ_COLORSPACE_CMYK ; 
 int FZ_COLORSPACE_GRAY ; 
 int FZ_COLORSPACE_LAB ; 
 int FZ_COLORSPACE_RGB ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/ * bgr_to_cmyk ; 
 int /*<<< orphan*/ * bgr_to_gray ; 
 int /*<<< orphan*/ * cmyk_to_bgr ; 
 int /*<<< orphan*/ * cmyk_to_cmyk ; 
 int /*<<< orphan*/ * cmyk_to_gray ; 
 int /*<<< orphan*/ * cmyk_to_rgb ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * gray_to_cmyk ; 
 int /*<<< orphan*/ * gray_to_gray ; 
 int /*<<< orphan*/ * gray_to_rgb ; 
 int /*<<< orphan*/ * lab_to_bgr ; 
 int /*<<< orphan*/ * lab_to_cmyk ; 
 int /*<<< orphan*/ * lab_to_gray ; 
 int /*<<< orphan*/ * lab_to_rgb ; 
 int /*<<< orphan*/ * rgb_to_bgr ; 
 int /*<<< orphan*/ * rgb_to_cmyk ; 
 int /*<<< orphan*/ * rgb_to_gray ; 
 int /*<<< orphan*/ * rgb_to_rgb ; 

fz_color_convert_fn *
fz_lookup_fast_color_converter(fz_context *ctx, fz_colorspace *ss, fz_colorspace *ds)
{
	int stype = ss->type;
	int dtype = ds->type;

	if (stype == FZ_COLORSPACE_GRAY)
	{
		if (dtype == FZ_COLORSPACE_GRAY) return gray_to_gray;
		if (dtype == FZ_COLORSPACE_RGB) return gray_to_rgb;
		if (dtype == FZ_COLORSPACE_BGR) return gray_to_rgb;
		if (dtype == FZ_COLORSPACE_CMYK) return gray_to_cmyk;
	}

	else if (stype == FZ_COLORSPACE_RGB)
	{
		if (dtype == FZ_COLORSPACE_GRAY) return rgb_to_gray;
		if (dtype == FZ_COLORSPACE_RGB) return rgb_to_rgb;
		if (dtype == FZ_COLORSPACE_BGR) return rgb_to_bgr;
		if (dtype == FZ_COLORSPACE_CMYK) return rgb_to_cmyk;
	}

	else if (stype == FZ_COLORSPACE_BGR)
	{
		if (dtype == FZ_COLORSPACE_GRAY) return bgr_to_gray;
		if (dtype == FZ_COLORSPACE_RGB) return rgb_to_bgr;
		if (dtype == FZ_COLORSPACE_BGR) return rgb_to_rgb;
		if (dtype == FZ_COLORSPACE_CMYK) return bgr_to_cmyk;
	}

	else if (stype == FZ_COLORSPACE_CMYK)
	{
		if (dtype == FZ_COLORSPACE_GRAY) return cmyk_to_gray;
		if (dtype == FZ_COLORSPACE_RGB) return cmyk_to_rgb;
		if (dtype == FZ_COLORSPACE_BGR) return cmyk_to_bgr;
		if (dtype == FZ_COLORSPACE_CMYK) return cmyk_to_cmyk;
	}

	else if (stype == FZ_COLORSPACE_LAB)
	{
		if (dtype == FZ_COLORSPACE_GRAY) return lab_to_gray;
		if (dtype == FZ_COLORSPACE_RGB) return lab_to_rgb;
		if (dtype == FZ_COLORSPACE_BGR) return lab_to_bgr;
		if (dtype == FZ_COLORSPACE_CMYK) return lab_to_cmyk;
	}

	fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find color converter");
}