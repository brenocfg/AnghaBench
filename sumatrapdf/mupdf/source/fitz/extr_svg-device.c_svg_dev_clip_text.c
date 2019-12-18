#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ text_as_text; int /*<<< orphan*/  id; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
struct TYPE_17__ {struct TYPE_17__* next; } ;
typedef  TYPE_2__ fz_text_span ;
struct TYPE_18__ {TYPE_2__* head; } ;
typedef  TYPE_3__ fz_text ;
struct TYPE_19__ {scalar_t__ y0; scalar_t__ y1; scalar_t__ x0; scalar_t__ x1; } ;
typedef  TYPE_4__ fz_rect ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  font ;

/* Variables and functions */
 int /*<<< orphan*/ * end_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_4__ fz_bound_text (int /*<<< orphan*/ *,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/  fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * start_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  svg_dev_fill_color (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_dev_text_span (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * svg_dev_text_span_as_paths_defs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_dev_text_span_as_paths_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,float,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svg_dev_clip_text(fz_context *ctx, fz_device *dev, const fz_text *text, fz_matrix ctm, fz_rect scissor)
{
	svg_device *sdev = (svg_device*)dev;
	fz_output *out = sdev->out;

	fz_rect bounds;
	int num = sdev->id++;
	float white[3] = { 1, 1, 1 };
	font *fnt;
	fz_text_span *span;

	bounds = fz_bound_text(ctx, text, NULL, ctm);

	out = start_def(ctx, sdev);
	fz_write_printf(ctx, out, "<mask id=\"ma%d\" x=\"%g\" y=\"%g\" width=\"%g\" height=\"%g\"",
			num, bounds.x0, bounds.y0, bounds.x1 - bounds.x0, bounds.y1 - bounds.y0);
	fz_write_printf(ctx, out, " maskUnits=\"userSpaceOnUse\" maskContentUnits=\"userSpaceOnUse\">\n");
	if (sdev->text_as_text)
	{
		for (span = text->head; span; span = span->next)
		{
			fz_write_printf(ctx, out, "<text");
			svg_dev_fill_color(ctx, sdev, fz_device_rgb(ctx), white, 1, fz_default_color_params);
			svg_dev_text_span(ctx, sdev, ctm, span);
		}
	}
	else
	{
		for (span = text->head; span; span = span->next)
		{
			fnt = svg_dev_text_span_as_paths_defs(ctx, dev, span, ctm);
			svg_dev_text_span_as_paths_fill(ctx, dev, span, ctm, fz_device_rgb(ctx), white, 1.0f, fnt, fz_default_color_params);
		}
	}
	fz_write_printf(ctx, out, "</mask>\n");
	out = end_def(ctx, sdev);
	fz_write_printf(ctx, out, "<g mask=\"url(#ma%d)\">\n", num);
}