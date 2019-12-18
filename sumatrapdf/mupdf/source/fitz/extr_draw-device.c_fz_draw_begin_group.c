#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rect ;
struct TYPE_13__ {scalar_t__ alpha; int /*<<< orphan*/ * seps; int /*<<< orphan*/ * colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_14__ {int blendmode; float alpha; int /*<<< orphan*/  scissor; TYPE_1__* group_alpha; TYPE_1__* shape; TYPE_1__* dest; } ;
typedef  TYPE_2__ fz_draw_state ;
struct TYPE_15__ {size_t top; int /*<<< orphan*/  default_cs; int /*<<< orphan*/  transform; scalar_t__ resolve_spots; TYPE_2__* stack; } ;
typedef  TYPE_3__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int FZ_BLEND_ISOLATED ; 
 int FZ_BLEND_KNOCKOUT ; 
 int /*<<< orphan*/  dump_spaces (int,char*) ; 
 int /*<<< orphan*/  fz_clear_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_copy_pixmap_rect (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/ * fz_default_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_dump_blend (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_intersect_irect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_irect_from_rect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_knockout_begin (int /*<<< orphan*/ *,TYPE_3__*) ; 
 void* fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_2__* push_group_for_separations (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* push_stack (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void
fz_draw_begin_group(fz_context *ctx, fz_device *devp, fz_rect area, fz_colorspace *cs, int isolated, int knockout, int blendmode, float alpha)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_irect bbox;
	fz_pixmap *dest;
	fz_draw_state *state = &dev->stack[dev->top];
	fz_colorspace *model = state->dest->colorspace;
	fz_rect trect;

	if (dev->top == 0 && dev->resolve_spots)
		state = push_group_for_separations(ctx, dev, fz_default_color_params /* FIXME */, dev->default_cs);

	if (cs != NULL)
		model = fz_default_colorspace(ctx, dev->default_cs, cs);

	if (state->blendmode & FZ_BLEND_KNOCKOUT)
		fz_knockout_begin(ctx, dev);

	state = push_stack(ctx, dev, "group");

	trect = fz_transform_rect(area, dev->transform);
	bbox = fz_intersect_irect(fz_irect_from_rect(trect), state->scissor);

#ifndef ATTEMPT_KNOCKOUT_AND_ISOLATED
	knockout = 0;
	isolated = 1;
#endif

	state[1].dest = dest = fz_new_pixmap_with_bbox(ctx, model, bbox, state[0].dest->seps, state[0].dest->alpha || isolated);

	if (isolated)
	{
		fz_clear_pixmap(ctx, dest);
		state[1].group_alpha = NULL;
	}
	else
	{
		fz_copy_pixmap_rect(ctx, dest, state[0].dest, bbox, dev->default_cs);
		state[1].group_alpha = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
		fz_clear_pixmap(ctx, state[1].group_alpha);
	}

	/* shape is inherited from the previous group */
	state[1].alpha = alpha;

#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top-1, "");
	{
		char text[240];
		char atext[80];
		char btext[80];
		if (alpha != 1)
			sprintf(atext, " (alpha %g)", alpha);
		else
			atext[0] = 0;
		if (blendmode != 0)
			sprintf(btext, " (blend %d)", blendmode);
		else
			btext[0] = 0;
		sprintf(text, "Group begin%s%s%s%s: background is ", isolated ? " (isolated)" : "", knockout ? " (knockout)" : "", atext, btext);
		fz_dump_blend(ctx, text, state[1].dest);
	}
	if (state[1].shape)
		fz_dump_blend(ctx, "/S=", state[1].shape);
	if (state[1].group_alpha)
		fz_dump_blend(ctx, "/GA=", state[1].group_alpha);
	printf("\n");
#endif

	state[1].scissor = bbox;
	state[1].blendmode = blendmode | (isolated ? FZ_BLEND_ISOLATED : 0) | (knockout ? FZ_BLEND_KNOCKOUT : 0);
}