#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_12__ {int blendmode; int /*<<< orphan*/  scissor; TYPE_5__* group_alpha; TYPE_5__* shape; TYPE_5__* dest; } ;
typedef  TYPE_1__ fz_draw_state ;
struct TYPE_13__ {size_t top; int /*<<< orphan*/  default_cs; TYPE_1__* stack; } ;
typedef  TYPE_2__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_14__ {int alpha; int /*<<< orphan*/ * seps; int /*<<< orphan*/ * colorspace; } ;

/* Variables and functions */
 int FZ_BLEND_ISOLATED ; 
 int FZ_BLEND_KNOCKOUT ; 
 int FZ_BLEND_MODEMASK ; 
 int /*<<< orphan*/  dump_spaces (int,char*) ; 
 int /*<<< orphan*/  fz_clear_pixmap (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  fz_copy_pixmap_rect (int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_dump_blend (int /*<<< orphan*/ *,char*,TYPE_5__*) ; 
 int /*<<< orphan*/  fz_intersect_irect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_pixmap_bbox (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* push_stack (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 

__attribute__((used)) static fz_draw_state *
fz_knockout_begin(fz_context *ctx, fz_draw_device *dev)
{
	fz_irect bbox, ga_bbox;
	fz_draw_state *state = &dev->stack[dev->top];
	int isolated = state->blendmode & FZ_BLEND_ISOLATED;

	if ((state->blendmode & FZ_BLEND_KNOCKOUT) == 0)
		return state;

	state = push_stack(ctx, dev, "knockout");

	bbox = fz_pixmap_bbox(ctx, state->dest);
	bbox = fz_intersect_irect(bbox, state->scissor);
	state[1].dest = fz_new_pixmap_with_bbox(ctx, state->dest->colorspace, bbox, state->dest->seps, state->dest->alpha);
	if (state[0].group_alpha)
	{
		ga_bbox = fz_pixmap_bbox(ctx, state->group_alpha);
		ga_bbox = fz_intersect_irect(ga_bbox, state->scissor);
		state[1].group_alpha = fz_new_pixmap_with_bbox(ctx, state->group_alpha->colorspace, ga_bbox, state->group_alpha->seps, state->group_alpha->alpha);
	}

	if (isolated)
	{
		fz_clear_pixmap(ctx, state[1].dest);
		if (state[1].group_alpha)
			fz_clear_pixmap(ctx, state[1].group_alpha);
	}
	else
	{
		/* Find the last but one destination to copy */
		int i = dev->top-1; /* i = the one on entry (i.e. the last one) */
		fz_draw_state *prev = state;
		while (i > 0)
		{
			prev = &dev->stack[--i];
			if (prev->dest != state->dest)
				break;
		}
		if (prev->dest)
		{
			fz_copy_pixmap_rect(ctx, state[1].dest, prev->dest, bbox, dev->default_cs);
			if (state[1].group_alpha)
			{
				if (prev->group_alpha)
					fz_copy_pixmap_rect(ctx, state[1].group_alpha, prev->group_alpha, ga_bbox, dev->default_cs);
				else
					fz_clear_pixmap(ctx, state[1].group_alpha);
			}
		}
		else
		{
			fz_clear_pixmap(ctx, state[1].dest);
			if (state[1].group_alpha)
				fz_clear_pixmap(ctx, state[1].group_alpha);
		}
	}

	/* Knockout groups (and only knockout groups) rely on shape */
	state[1].shape = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
	fz_clear_pixmap(ctx, state[1].shape);

#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top-1, "");
	fz_dump_blend(ctx, "Knockout begin: background is ", state[1].dest);
	if (state[1].shape)
		fz_dump_blend(ctx, "/S=", state[1].shape);
	if (state[1].group_alpha)
		fz_dump_blend(ctx, "/GA=", state[1].group_alpha);
	printf("\n");
#endif

	state[1].scissor = bbox;
	state[1].blendmode &= ~(FZ_BLEND_MODEMASK | FZ_BLEND_ISOLATED);

	return &state[1];
}