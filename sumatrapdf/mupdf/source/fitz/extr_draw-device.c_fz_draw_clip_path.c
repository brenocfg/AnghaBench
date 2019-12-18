#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  void* fz_irect ;
struct TYPE_10__ {void* scissor; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * group_alpha; int /*<<< orphan*/ * shape; TYPE_7__* dest; } ;
typedef  TYPE_1__ fz_draw_state ;
struct TYPE_11__ {size_t top; int /*<<< orphan*/  default_cs; int /*<<< orphan*/  transform; scalar_t__ resolve_spots; TYPE_1__* stack; int /*<<< orphan*/ * rast; } ;
typedef  TYPE_2__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
struct TYPE_12__ {int alpha; int /*<<< orphan*/ * seps; int /*<<< orphan*/ * colorspace; } ;

/* Variables and functions */
 float FLT_EPSILON ; 
 int /*<<< orphan*/  dump_spaces (int,char*) ; 
 int /*<<< orphan*/  fz_clear_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_convert_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_copy_pixmap_rect (int /*<<< orphan*/ *,TYPE_7__*,TYPE_7__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 scalar_t__ fz_flatten_fill_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,float,void**,void**) ; 
 void* fz_intersect_irect (void*,void*) ; 
 void* fz_irect_from_rect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_is_infinite_rect (int /*<<< orphan*/ ) ; 
 scalar_t__ fz_is_rect_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 float fz_matrix_expansion (int /*<<< orphan*/ ) ; 
 void* fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int) ; 
 void* fz_pixmap_bbox (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* push_group_for_separations (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* push_stack (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 

__attribute__((used)) static void
fz_draw_clip_path(fz_context *ctx, fz_device *devp, const fz_path *path, int even_odd, fz_matrix in_ctm, fz_rect scissor)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_matrix ctm = fz_concat(in_ctm, dev->transform);
	fz_rasterizer *rast = dev->rast;

	float expansion = fz_matrix_expansion(ctm);
	float flatness;
	fz_irect bbox;
	fz_draw_state *state = &dev->stack[dev->top];
	fz_colorspace *model;

	if (dev->top == 0 && dev->resolve_spots)
		state = push_group_for_separations(ctx, dev, fz_default_color_params /* FIXME */, dev->default_cs);

	if (expansion < FLT_EPSILON)
		expansion = 1;
	flatness = 0.3f / expansion;
	if (flatness < 0.001f)
		flatness = 0.001f;

	state = push_stack(ctx, dev, "clip path");

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

	if (fz_flatten_fill_path(ctx, rast, path, ctm, flatness, &bbox, &bbox) || fz_is_rect_rasterizer(ctx, rast))
	{
		state[1].scissor = bbox;
		state[1].mask = NULL;
#ifdef DUMP_GROUP_BLENDS
		dump_spaces(dev->top-1, "Clip (rectangular) begin\n");
#endif
		return;
	}

	state[1].mask = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
	fz_clear_pixmap(ctx, state[1].mask);
	state[1].dest = fz_new_pixmap_with_bbox(ctx, model, bbox, state[0].dest->seps, state[0].dest->alpha);
	fz_copy_pixmap_rect(ctx, state[1].dest, state[0].dest, bbox, dev->default_cs);
	if (state[1].shape)
	{
		state[1].shape = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
		fz_clear_pixmap(ctx, state[1].shape);
	}
	if (state[1].group_alpha)
	{
		state[1].group_alpha = fz_new_pixmap_with_bbox(ctx, NULL, bbox, NULL, 1);
		fz_clear_pixmap(ctx, state[1].group_alpha);
	}

	fz_convert_rasterizer(ctx, rast, even_odd, state[1].mask, NULL, 0);

	state[1].scissor = bbox;

#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top-1, "Clip (non-rectangular) begin\n");
#endif
}