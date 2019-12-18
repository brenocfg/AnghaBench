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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float fz_colorspace_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
fz_trace_color(fz_context *ctx, fz_output *out, fz_colorspace *colorspace, const float *color, float alpha)
{
	int i, n;
	if (colorspace)
	{
		n = fz_colorspace_n(ctx, colorspace);
		fz_write_printf(ctx, out, " colorspace=\"%s\" color=\"", fz_colorspace_name(ctx, colorspace));
		for (i = 0; i < n; i++)
			fz_write_printf(ctx, out, "%s%g", i == 0 ? "" : " ", color[i]);
		fz_write_printf(ctx, out, "\"");
	}
	if (alpha < 1)
		fz_write_printf(ctx, out, " alpha=\"%g\"", alpha);
}