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
struct TYPE_5__ {int /*<<< orphan*/ * group_alpha; int /*<<< orphan*/ * shape; int /*<<< orphan*/ * dest; int /*<<< orphan*/ * mask; } ;
typedef  TYPE_1__ fz_draw_state ;
struct TYPE_6__ {scalar_t__ top; } ;
typedef  TYPE_2__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  dump_spaces (scalar_t__,char*) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_dump_blend (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_paint_pixmap_with_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* pop_stack (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
fz_draw_pop_clip(fz_context *ctx, fz_device *devp)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_draw_state *state;

	if (dev->top == 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "unexpected pop clip");

	state = pop_stack(ctx, dev, "clip");

	/* We can get here with state[1].mask == NULL if the clipping actually
	 * resolved to a rectangle earlier.
	 */
	if (state[1].mask)
	{
#ifdef DUMP_GROUP_BLENDS
		dump_spaces(dev->top, "");
		fz_dump_blend(ctx, "Clipping ", state[1].dest);
		if (state[1].shape)
			fz_dump_blend(ctx, "/S=", state[1].shape);
		if (state[1].group_alpha)
			fz_dump_blend(ctx, "/GA=", state[1].group_alpha);
		fz_dump_blend(ctx, " onto ", state[0].dest);
		if (state[0].shape)
			fz_dump_blend(ctx, "/S=", state[0].shape);
		if (state[0].group_alpha)
			fz_dump_blend(ctx, "/GA=", state[0].group_alpha);
		fz_dump_blend(ctx, " with ", state[1].mask);
#endif

		fz_paint_pixmap_with_mask(state[0].dest, state[1].dest, state[1].mask);
		if (state[0].shape != state[1].shape)
		{
			fz_paint_pixmap_with_mask(state[0].shape, state[1].shape, state[1].mask);
			fz_drop_pixmap(ctx, state[1].shape);
			state[1].shape = NULL;
		}
		if (state[0].group_alpha != state[1].group_alpha)
		{
			fz_paint_pixmap_with_mask(state[0].group_alpha, state[1].group_alpha, state[1].mask);
			fz_drop_pixmap(ctx, state[1].group_alpha);
			state[1].group_alpha = NULL;
		}
		fz_drop_pixmap(ctx, state[1].mask);
		state[1].mask = NULL;
		fz_drop_pixmap(ctx, state[1].dest);
		state[1].dest = NULL;

#ifdef DUMP_GROUP_BLENDS
		fz_dump_blend(ctx, " to get ", state[0].dest);
		if (state[0].shape)
			fz_dump_blend(ctx, "/S=", state[0].shape);
		if (state[0].group_alpha)
			fz_dump_blend(ctx, "/GA=", state[0].group_alpha);
		printf("\n");
#endif
	}
	else
	{
#ifdef DUMP_GROUP_BLENDS
		dump_spaces(dev->top, "Clip end\n");
#endif
	}
}