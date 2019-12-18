#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ text_as_text; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_2__ fz_text_span ;
struct TYPE_10__ {TYPE_2__* head; } ;
typedef  TYPE_3__ fz_text ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/  fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svg_dev_fill_color (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,float*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_dev_text_span (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
svg_dev_ignore_text(fz_context *ctx, fz_device *dev, const fz_text *text, fz_matrix ctm)
{
	svg_device *sdev = (svg_device*)dev;
	fz_output *out = sdev->out;
	fz_text_span *span;

	float black[3] = { 0, 0, 0};

	if (sdev->text_as_text)
	{
		for (span = text->head; span; span = span->next)
		{
			fz_write_printf(ctx, out, "<text");
			svg_dev_fill_color(ctx, sdev, fz_device_rgb(ctx), black, 0.0f, fz_default_color_params);
			svg_dev_text_span(ctx, sdev, ctm, span);
		}
	}
}