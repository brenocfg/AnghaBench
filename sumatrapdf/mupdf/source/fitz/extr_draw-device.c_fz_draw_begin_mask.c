#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_7__ {int /*<<< orphan*/  scissor; int /*<<< orphan*/ * group_alpha; int /*<<< orphan*/ * shape; int /*<<< orphan*/ * dest; scalar_t__ blendmode; } ;
typedef  TYPE_1__ fz_draw_state ;
struct TYPE_8__ {scalar_t__ top; int /*<<< orphan*/  transform; int /*<<< orphan*/  default_cs; scalar_t__ resolve_spots; } ;
typedef  TYPE_2__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  dump_spaces (scalar_t__,char*) ; 
 int /*<<< orphan*/  fz_clear_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_clear_pixmap_with_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_convert_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_default_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_device_gray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_intersect_irect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_irect_from_rect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* push_group_for_separations (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* push_stack (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 

__attribute__((used)) static void
fz_draw_begin_mask(fz_context *ctx, fz_device *devp, fz_rect area, int luminosity, fz_colorspace *colorspace_in, const float *colorfv, fz_color_params color_params)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_pixmap *dest;
	fz_irect bbox;
	fz_draw_state *state = push_stack(ctx, dev, "mask");
	fz_pixmap *shape = state->shape;
	fz_pixmap *group_alpha = state->group_alpha;
	fz_rect trect;
	fz_colorspace *colorspace = NULL;

	if (dev->top == 0 && dev->resolve_spots)
		state = push_group_for_separations(ctx, dev, color_params, dev->default_cs);

	if (colorspace_in)
		colorspace = fz_default_colorspace(ctx, dev->default_cs, colorspace_in);

	trect = fz_transform_rect(area, dev->transform);
	bbox = fz_intersect_irect(fz_irect_from_rect(trect), state->scissor);

	/* Reset the blendmode for the mask rendering. In particular,
	 * don't carry forward knockout or isolated. */
	state[1].blendmode = 0;

	/* If luminosity, then we generate a mask from the greyscale value of the shapes.
	 * If !luminosity, then we generate a mask from the alpha value of the shapes.
	 */
	if (luminosity)
		state[1].dest = dest = fz_new_pixmap_with_bbox(ctx, fz_device_gray(ctx), bbox, NULL, 0);
	else
		state[1].dest = dest = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
	if (state->shape)
	{
		/* FIXME: If we ever want to support AIS true, then
		 * we probably want to create a shape pixmap here,
		 * using: shape = fz_new_pixmap_with_bbox(NULL, bbox);
		 * then, in the end_mask code, we create the mask
		 * from this rather than dest.
		 */
		state[1].shape = shape = NULL;
	}
	if (state->group_alpha)
	{
		state[1].group_alpha = group_alpha = NULL;
	}

	if (luminosity)
	{
		float bc;
		if (!colorspace)
			colorspace = fz_device_gray(ctx);
		fz_convert_color(ctx, colorspace, colorfv, fz_device_gray(ctx), &bc, NULL, color_params);
		fz_clear_pixmap_with_value(ctx, dest, bc * 255);
		if (shape)
			fz_clear_pixmap_with_value(ctx, shape, 255);
		if (group_alpha)
			fz_clear_pixmap_with_value(ctx, group_alpha, 255);
	}
	else
	{
		fz_clear_pixmap(ctx, dest);
		if (shape)
			fz_clear_pixmap(ctx, shape);
		if (group_alpha)
			fz_clear_pixmap(ctx, group_alpha);
	}

#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top-1, "Mask begin\n");
#endif
	state[1].scissor = bbox;
}