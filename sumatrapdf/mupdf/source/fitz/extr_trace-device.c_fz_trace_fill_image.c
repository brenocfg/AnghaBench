#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  depth; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ fz_trace_device ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_5__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; scalar_t__ colorspace; } ;
typedef  TYPE_2__ fz_image ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  fz_colorspace_name (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fz_trace_indent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_trace_matrix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
fz_trace_fill_image(fz_context *ctx, fz_device *dev_, fz_image *image, fz_matrix ctm, float alpha, fz_color_params color_params)
{
	fz_trace_device *dev = (fz_trace_device*)dev_;
	fz_output *out = dev->out;
	fz_trace_indent(ctx, out, dev->depth);
	fz_write_printf(ctx, out, "<fill_image alpha=\"%g\"", alpha);
	if (image->colorspace)
		fz_write_printf(ctx, out, " colorspace=\"%s\"", fz_colorspace_name(ctx, image->colorspace));
	fz_trace_matrix(ctx, out, ctm);
	fz_write_printf(ctx, out, " width=\"%d\" height=\"%d\"", image->w, image->h);
	fz_write_printf(ctx, out, "/>\n");
}