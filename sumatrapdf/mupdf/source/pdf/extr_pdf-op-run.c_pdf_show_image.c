#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ softmask_save ;
struct TYPE_15__ {scalar_t__ hidden; } ;
struct TYPE_17__ {int gtop; int /*<<< orphan*/  dev; TYPE_1__ super; TYPE_4__* gstate; } ;
typedef  TYPE_3__ pdf_run_processor ;
struct TYPE_18__ {scalar_t__ blendmode; int /*<<< orphan*/  ctm; } ;
typedef  TYPE_4__ pdf_gstate ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_19__ {scalar_t__ mask; } ;
typedef  TYPE_5__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_begin_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  fz_clip_image_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_end_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pop_clip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pre_scale (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fz_pre_translate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unit_rect ; 
 TYPE_4__* pdf_begin_group (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pdf_end_group (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pdf_show_image_imp (int /*<<< orphan*/ *,TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_show_image(fz_context *ctx, pdf_run_processor *pr, fz_image *image)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;
	fz_matrix image_ctm;
	fz_rect bbox;

	if (pr->super.hidden)
		return;

	/* PDF has images bottom-up, so flip them right side up here */
	image_ctm = fz_pre_scale(fz_pre_translate(gstate->ctm, 0, 1), 1, -1);

	bbox = fz_transform_rect(fz_unit_rect, image_ctm);

	if (image->mask && gstate->blendmode)
	{
		/* apply blend group even though we skip the soft mask */
		fz_begin_group(ctx, pr->dev, bbox, NULL, 0, 0, gstate->blendmode, 1);
		fz_clip_image_mask(ctx, pr->dev, image->mask, image_ctm, bbox);
		pdf_show_image_imp(ctx, pr, image, image_ctm, bbox);
		fz_pop_clip(ctx, pr->dev);
		fz_end_group(ctx, pr->dev);
	}
	else if (image->mask)
	{
		fz_clip_image_mask(ctx, pr->dev, image->mask, image_ctm, bbox);
		pdf_show_image_imp(ctx, pr, image, image_ctm, bbox);
		fz_pop_clip(ctx, pr->dev);
	}
	else
	{
		softmask_save softmask = { NULL };
		gstate = pdf_begin_group(ctx, pr, bbox, &softmask);
		pdf_show_image_imp(ctx, pr, image, image_ctm, bbox);
		pdf_end_group(ctx, pr, &softmask);
	}
}