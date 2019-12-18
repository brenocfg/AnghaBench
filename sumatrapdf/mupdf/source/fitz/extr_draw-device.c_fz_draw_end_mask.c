#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int alpha; int /*<<< orphan*/ * seps; int /*<<< orphan*/ * colorspace; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_15__ {int /*<<< orphan*/  scissor; TYPE_1__* group_alpha; TYPE_1__* shape; int /*<<< orphan*/  blendmode; TYPE_1__* dest; TYPE_1__* mask; } ;
typedef  TYPE_2__ fz_draw_state ;
struct TYPE_16__ {scalar_t__ top; int /*<<< orphan*/  default_cs; } ;
typedef  TYPE_3__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_BLEND_ISOLATED ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 TYPE_2__* convert_stack (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dump_spaces (scalar_t__,char*) ; 
 TYPE_1__* fz_alpha_from_gray (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_clear_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_copy_pixmap_rect (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_dump_blend (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 void* fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_pixmap_bbox (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
fz_draw_end_mask(fz_context *ctx, fz_device *devp)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_pixmap *temp, *dest;
	fz_irect bbox;
	fz_draw_state *state;

	if (dev->top == 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "unexpected end mask");

	state = convert_stack(ctx, dev, "mask");

#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top-1, "Mask -> Clip: ");
	fz_dump_blend(ctx, "Mask ", state[1].dest);
	if (state[1].shape)
		fz_dump_blend(ctx, "/S=", state[1].shape);
	if (state[1].group_alpha)
		fz_dump_blend(ctx, "/GA=", state[1].group_alpha);
#endif
	{
		/* convert to alpha mask */
		temp = fz_alpha_from_gray(ctx, state[1].dest);
		if (state[1].mask != state[0].mask)
			fz_drop_pixmap(ctx, state[1].mask);
		state[1].mask = temp;
		if (state[1].dest != state[0].dest)
			fz_drop_pixmap(ctx, state[1].dest);
		state[1].dest = NULL;
		if (state[1].shape != state[0].shape)
			fz_drop_pixmap(ctx, state[1].shape);
		state[1].shape = NULL;
		if (state[1].group_alpha != state[0].group_alpha)
			fz_drop_pixmap(ctx, state[1].group_alpha);
		state[1].group_alpha = NULL;

#ifdef DUMP_GROUP_BLENDS
		fz_dump_blend(ctx, "-> Clip ", temp);
		printf("\n");
#endif

		/* create new dest scratch buffer */
		bbox = fz_pixmap_bbox(ctx, temp);
		dest = fz_new_pixmap_with_bbox(ctx, state->dest->colorspace, bbox, state->dest->seps, state->dest->alpha);
		fz_copy_pixmap_rect(ctx, dest, state->dest, bbox, dev->default_cs);

		/* push soft mask as clip mask */
		state[1].dest = dest;
		state[1].blendmode |= FZ_BLEND_ISOLATED;
		/* If we have a shape, then it'll need to be masked with the
		 * clip mask when we pop. So create a new shape now. */
		if (state[0].shape)
		{
			state[1].shape = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
			fz_clear_pixmap(ctx, state[1].shape);
		}
		if (state[0].group_alpha)
		{
			state[1].group_alpha = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
			fz_clear_pixmap(ctx, state[1].group_alpha);
		}
		state[1].scissor = bbox;
	}
}