#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ text_as_text; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
struct TYPE_11__ {struct TYPE_11__* next; } ;
typedef  TYPE_2__ fz_text_span ;
struct TYPE_12__ {TYPE_2__* head; } ;
typedef  TYPE_3__ fz_text ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;
typedef  int /*<<< orphan*/  font ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svg_dev_fill_color (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,float const*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_dev_text_span (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * svg_dev_text_span_as_paths_defs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_dev_text_span_as_paths_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,float const*,float,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svg_dev_fill_text(fz_context *ctx, fz_device *dev, const fz_text *text, fz_matrix ctm,
	fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	svg_device *sdev = (svg_device*)dev;
	fz_output *out = sdev->out;
	font *fnt;
	fz_text_span *span;

	if (sdev->text_as_text)
	{
		for (span = text->head; span; span = span->next)
		{
			fz_write_printf(ctx, out, "<text");
			svg_dev_fill_color(ctx, sdev, colorspace, color, alpha, color_params);
			svg_dev_text_span(ctx, sdev, ctm, span);
		}
	}
	else
	{
		for (span = text->head; span; span = span->next)
		{
			fnt = svg_dev_text_span_as_paths_defs(ctx, dev, span, ctm);
			svg_dev_text_span_as_paths_fill(ctx, dev, span, ctm, colorspace, color, alpha, fnt, color_params);
		}
	}
}