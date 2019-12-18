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
struct TYPE_3__ {int* is_color; int resolved; int /*<<< orphan*/ * passthrough; int /*<<< orphan*/  threshold; } ;
typedef  TYPE_1__ fz_test_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_GRAY ; 
 int /*<<< orphan*/  FZ_ERROR_ABORT ; 
 scalar_t__ fz_colorspace_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_convert_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_rgb_color (int /*<<< orphan*/ ,float const,float const,float const) ; 

__attribute__((used)) static void
fz_test_color(fz_context *ctx, fz_test_device *t, fz_colorspace *colorspace, const float *color, fz_color_params color_params)
{
	if (!*t->is_color && colorspace && fz_colorspace_type(ctx, colorspace) != FZ_COLORSPACE_GRAY)
	{
		if (colorspace == fz_device_rgb(ctx))
		{
			if (is_rgb_color(t->threshold, color[0], color[1], color[2]))
			{
				*t->is_color = 2;
				t->resolved = 1;
				if (t->passthrough == NULL)
					fz_throw(ctx, FZ_ERROR_ABORT, "Page found as color; stopping interpretation");
			}
		}
		else
		{
			float rgb[3];
			fz_convert_color(ctx, colorspace, color, fz_device_rgb(ctx), rgb, NULL, color_params);
			if (is_rgb_color(t->threshold, rgb[0], rgb[1], rgb[2]))
			{
				*t->is_color = 2;
				t->resolved = 1;
				if (t->passthrough == NULL)
				{
					fz_throw(ctx, FZ_ERROR_ABORT, "Page found as color; stopping interpretation");
				}
			}
		}
	}
}