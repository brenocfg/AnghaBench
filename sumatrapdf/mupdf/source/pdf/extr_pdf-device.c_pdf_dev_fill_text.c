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
typedef  int /*<<< orphan*/  pdf_device ;
struct TYPE_5__ {int /*<<< orphan*/  trm; int /*<<< orphan*/  font; struct TYPE_5__* next; } ;
typedef  TYPE_1__ fz_text_span ;
struct TYPE_6__ {TYPE_1__* head; } ;
typedef  TYPE_2__ fz_text ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_dev_alpha (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_begin_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_ctm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_font (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_text_span (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
pdf_dev_fill_text(fz_context *ctx, fz_device *dev, const fz_text *text, fz_matrix ctm,
		fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	pdf_device *pdev = (pdf_device*)dev;
	fz_text_span *span;

	pdf_dev_ctm(ctx, pdev, ctm);
	pdf_dev_alpha(ctx, pdev, alpha, 0);
	pdf_dev_color(ctx, pdev, colorspace, color, 0, color_params);

	for (span = text->head; span; span = span->next)
	{
		pdf_dev_begin_text(ctx, pdev, 0);
		pdf_dev_font(ctx, pdev, span->font, span->trm);
		pdf_dev_text_span(ctx, pdev, span);
	}
}