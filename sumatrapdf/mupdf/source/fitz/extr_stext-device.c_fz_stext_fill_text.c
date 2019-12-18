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
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_1__ fz_text_span ;
struct TYPE_11__ {TYPE_1__* head; } ;
typedef  TYPE_2__ fz_text ;
struct TYPE_12__ {int new_obj; TYPE_2__ const* lasttext; int /*<<< orphan*/  color; } ;
typedef  TYPE_3__ fz_stext_device ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_text (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 TYPE_2__ const* fz_keep_text (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  fz_stext_extract (int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexrgb_from_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*) ; 

__attribute__((used)) static void
fz_stext_fill_text(fz_context *ctx, fz_device *dev, const fz_text *text, fz_matrix ctm,
	fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	fz_stext_device *tdev = (fz_stext_device*)dev;
	fz_text_span *span;
	if (text == tdev->lasttext)
		return;
	tdev->color = hexrgb_from_color(ctx, colorspace, color);
	tdev->new_obj = 1;
	for (span = text->head; span; span = span->next)
		fz_stext_extract(ctx, tdev, span, ctm);
	fz_drop_text(ctx, tdev->lasttext);
	tdev->lasttext = fz_keep_text(ctx, text);
}