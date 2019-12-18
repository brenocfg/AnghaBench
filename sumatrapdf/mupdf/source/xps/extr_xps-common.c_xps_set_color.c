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
struct TYPE_3__ {float* color; float alpha; float* opacity; size_t opacity_top; int /*<<< orphan*/ * colorspace; } ;
typedef  TYPE_1__ xps_document ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
xps_set_color(fz_context *ctx, xps_document *doc, fz_colorspace *colorspace, float *samples)
{
	int i;
	int n = fz_colorspace_n(ctx, colorspace);
	doc->colorspace = colorspace;
	for (i = 0; i < n; i++)
		doc->color[i] = samples[i + 1];
	doc->alpha = samples[0] * doc->opacity[doc->opacity_top];
}