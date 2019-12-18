#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  depth; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ fz_trace_device ;
struct TYPE_6__ {int dash_len; int /*<<< orphan*/ * dash_list; int /*<<< orphan*/  dash_phase; int /*<<< orphan*/  linejoin; int /*<<< orphan*/  end_cap; int /*<<< orphan*/  dash_cap; int /*<<< orphan*/  start_cap; int /*<<< orphan*/  miterlimit; int /*<<< orphan*/  linewidth; } ;
typedef  TYPE_2__ fz_stroke_state ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  fz_trace_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,float) ; 
 int /*<<< orphan*/  fz_trace_indent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_trace_matrix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_trace_path (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
fz_trace_stroke_path(fz_context *ctx, fz_device *dev_, const fz_path *path, const fz_stroke_state *stroke, fz_matrix ctm,
	fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	fz_trace_device *dev = (fz_trace_device*)dev_;
	fz_output *out = dev->out;
	int i;

	fz_trace_indent(ctx, out, dev->depth);
	fz_write_printf(ctx, out, "<stroke_path");
	fz_write_printf(ctx, out, " linewidth=\"%g\"", stroke->linewidth);
	fz_write_printf(ctx, out, " miterlimit=\"%g\"", stroke->miterlimit);
	fz_write_printf(ctx, out, " linecap=\"%d,%d,%d\"", stroke->start_cap, stroke->dash_cap, stroke->end_cap);
	fz_write_printf(ctx, out, " linejoin=\"%d\"", stroke->linejoin);

	if (stroke->dash_len)
	{
		fz_write_printf(ctx, out, " dash_phase=\"%g\" dash=\"", stroke->dash_phase);
		for (i = 0; i < stroke->dash_len; i++)
			fz_write_printf(ctx, out, "%s%g", i > 0 ? " " : "", stroke->dash_list[i]);
		fz_write_printf(ctx, out, "\"");
	}

	fz_trace_color(ctx, out, colorspace, color, alpha);
	fz_trace_matrix(ctx, out, ctm);
	fz_write_printf(ctx, out, ">\n");

	fz_trace_path(ctx, dev, path);

	fz_trace_indent(ctx, out, dev->depth);
	fz_write_printf(ctx, out, "</stroke_path>\n");
}