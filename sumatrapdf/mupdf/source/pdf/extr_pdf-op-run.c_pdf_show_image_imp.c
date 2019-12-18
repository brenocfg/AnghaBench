#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int gtop; int /*<<< orphan*/  dev; TYPE_3__* gstate; } ;
typedef  TYPE_2__ pdf_run_processor ;
struct TYPE_12__ {scalar_t__ kind; size_t gstate_num; int /*<<< orphan*/  color_params; int /*<<< orphan*/  alpha; scalar_t__ shade; scalar_t__ pattern; int /*<<< orphan*/  v; int /*<<< orphan*/  colorspace; } ;
struct TYPE_14__ {TYPE_1__ fill; int /*<<< orphan*/  ctm; } ;
typedef  TYPE_3__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_15__ {scalar_t__ colorspace; } ;
typedef  TYPE_4__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_FILL ; 
 scalar_t__ PDF_MAT_COLOR ; 
 scalar_t__ PDF_MAT_PATTERN ; 
 scalar_t__ PDF_MAT_SHADE ; 
 int /*<<< orphan*/  fz_clip_image_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_fill_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_fill_image_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_fill_shade (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pop_clip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* pdf_show_pattern (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_show_image_imp(fz_context *ctx, pdf_run_processor *pr, fz_image *image, fz_matrix image_ctm, fz_rect bbox)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;

	if (image->colorspace)
	{
		fz_fill_image(ctx, pr->dev, image, image_ctm, gstate->fill.alpha, gstate->fill.color_params);
	}
	else if (gstate->fill.kind == PDF_MAT_COLOR)
	{
		fz_fill_image_mask(ctx, pr->dev, image, image_ctm, gstate->fill.colorspace, gstate->fill.v, gstate->fill.alpha, gstate->fill.color_params);
	}
	else if (gstate->fill.kind == PDF_MAT_PATTERN && gstate->fill.pattern)
	{
		fz_clip_image_mask(ctx, pr->dev, image, image_ctm, bbox);
		gstate = pdf_show_pattern(ctx, pr, gstate->fill.pattern, gstate->fill.gstate_num, bbox, PDF_FILL);
		fz_pop_clip(ctx, pr->dev);
	}
	else if (gstate->fill.kind == PDF_MAT_SHADE && gstate->fill.shade)
	{
		fz_clip_image_mask(ctx, pr->dev, image, image_ctm, bbox);
		fz_fill_shade(ctx, pr->dev, gstate->fill.shade, pr->gstate[gstate->fill.gstate_num].ctm, gstate->fill.alpha, gstate->fill.color_params);
		fz_pop_clip(ctx, pr->dev);
	}
}