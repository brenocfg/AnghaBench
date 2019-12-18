#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {float linewidth; } ;
typedef  TYPE_1__ fz_stroke_state ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  void* fz_irect ;
struct TYPE_16__ {void* scissor; int /*<<< orphan*/  blendmode; TYPE_8__* mask; TYPE_8__* group_alpha; TYPE_8__* shape; TYPE_8__* dest; } ;
typedef  TYPE_2__ fz_draw_state ;
struct TYPE_17__ {size_t top; int /*<<< orphan*/  default_cs; int /*<<< orphan*/  transform; scalar_t__ resolve_spots; TYPE_2__* stack; int /*<<< orphan*/ * rast; } ;
typedef  TYPE_3__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
struct TYPE_18__ {int alpha; int /*<<< orphan*/ * seps; int /*<<< orphan*/ * colorspace; } ;

/* Variables and functions */
 float FLT_EPSILON ; 
 int /*<<< orphan*/  FZ_BLEND_ISOLATED ; 
 int /*<<< orphan*/  dump_spaces (int,char*) ; 
 int /*<<< orphan*/  fz_clear_pixmap (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_convert_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_copy_pixmap_rect (int /*<<< orphan*/ *,TYPE_8__*,TYPE_8__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 scalar_t__ fz_flatten_stroke_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ ,float,float,void**,void**) ; 
 void* fz_intersect_irect (void*,void*) ; 
 void* fz_irect_from_rect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_is_infinite_rect (int /*<<< orphan*/ ) ; 
 float fz_matrix_expansion (int /*<<< orphan*/ ) ; 
 void* fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int) ; 
 void* fz_pixmap_bbox (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int fz_rasterizer_graphics_aa_level (int /*<<< orphan*/ *) ; 
 float fz_rasterizer_graphics_min_line_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* push_group_for_separations (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* push_stack (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 

__attribute__((used)) static void
fz_draw_clip_stroke_path(fz_context *ctx, fz_device *devp, const fz_path *path, const fz_stroke_state *stroke, fz_matrix in_ctm, fz_rect scissor)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_matrix ctm = fz_concat(in_ctm, dev->transform);
	fz_rasterizer *rast = dev->rast;

	float expansion = fz_matrix_expansion(ctm);
	float flatness;
	float linewidth = stroke->linewidth;
	fz_irect bbox;
	fz_draw_state *state = &dev->stack[dev->top];
	fz_colorspace *model;
	float aa_level = 2.0f/(fz_rasterizer_graphics_aa_level(rast)+2);
	float mlw = fz_rasterizer_graphics_min_line_width(rast);

	if (dev->top == 0 && dev->resolve_spots)
		state = push_group_for_separations(ctx, dev, fz_default_color_params /* FIXME */, dev->default_cs);

	if (mlw > aa_level)
		aa_level = mlw;
	if (expansion < FLT_EPSILON)
		expansion = 1;
	if (linewidth * expansion < aa_level)
		linewidth = aa_level / expansion;
	flatness = 0.3f / expansion;
	if (flatness < 0.001f)
		flatness = 0.001f;

	state = push_stack(ctx, dev, "clip stroke");

	model = state->dest->colorspace;

	if (!fz_is_infinite_rect(scissor))
	{
		bbox = fz_irect_from_rect(fz_transform_rect(scissor, dev->transform));
		bbox = fz_intersect_irect(bbox, fz_pixmap_bbox(ctx, state->dest));
		bbox = fz_intersect_irect(bbox, state->scissor);
	}
	else
	{
		bbox = fz_intersect_irect(fz_pixmap_bbox(ctx, state->dest), state->scissor);
	}

	if (fz_flatten_stroke_path(ctx, rast, path, stroke, ctm, flatness, linewidth, &bbox, &bbox))
	{
		state[1].scissor = bbox;
		state[1].mask = NULL;
#ifdef DUMP_GROUP_BLENDS
		dump_spaces(dev->top-1, "Clip (stroke, empty) begin\n");
#endif
		return;
	}

	state[1].mask = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
	fz_clear_pixmap(ctx, state[1].mask);
	/* When there is no alpha in the current destination (state[0].dest->alpha == 0)
	 * we have a choice. We can either create the new destination WITH alpha, or
	 * we can copy the old pixmap contents in. We opt for the latter here, but
	 * may want to revisit this decision in the future. */
	state[1].dest = fz_new_pixmap_with_bbox(ctx, model, bbox, state[0].dest->seps, state[0].dest->alpha);
	if (state[0].dest->alpha)
		fz_clear_pixmap(ctx, state[1].dest);
	else
		fz_copy_pixmap_rect(ctx, state[1].dest, state[0].dest, bbox, dev->default_cs);
	if (state->shape)
	{
		state[1].shape = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
		fz_clear_pixmap(ctx, state[1].shape);
	}
	if (state->group_alpha)
	{
		state[1].group_alpha = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
		fz_clear_pixmap(ctx, state[1].group_alpha);
	}

	fz_convert_rasterizer(ctx, rast, 0, state[1].mask, NULL, 0);

	state[1].blendmode |= FZ_BLEND_ISOLATED;
	state[1].scissor = bbox;

#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top-1, "Clip (stroke) begin\n");
#endif
}