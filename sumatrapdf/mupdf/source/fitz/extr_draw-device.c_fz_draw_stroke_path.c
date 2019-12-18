#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {float linewidth; } ;
typedef  TYPE_3__ fz_stroke_state ;
struct TYPE_23__ {int /*<<< orphan*/  reusable; } ;
struct TYPE_25__ {TYPE_2__ fns; } ;
typedef  TYPE_4__ fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_path ;
struct TYPE_22__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_26__ {TYPE_1__ member_0; } ;
typedef  TYPE_5__ fz_overprint ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_27__ {int blendmode; scalar_t__ group_alpha; scalar_t__ shape; scalar_t__ dest; int /*<<< orphan*/  scissor; } ;
typedef  TYPE_6__ fz_draw_state ;
struct TYPE_28__ {size_t top; int /*<<< orphan*/  default_cs; scalar_t__ resolve_spots; TYPE_6__* stack; TYPE_4__* rast; int /*<<< orphan*/  transform; } ;
typedef  TYPE_7__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 float FLT_EPSILON ; 
 int FZ_BLEND_KNOCKOUT ; 
 int /*<<< orphan*/  FZ_MAX_COLORS ; 
 int /*<<< orphan*/  dump_spaces (size_t,char*) ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_convert_rasterizer (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,unsigned char*,TYPE_5__*) ; 
 int /*<<< orphan*/ * fz_default_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_dump_blend (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ fz_flatten_stroke_path (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/  const*,TYPE_3__ const*,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_intersect_irect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* fz_knockout_begin (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  fz_knockout_end (int /*<<< orphan*/ *,TYPE_7__*) ; 
 float fz_matrix_expansion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pixmap_bbox_no_ctx (scalar_t__) ; 
 int fz_rasterizer_graphics_aa_level (TYPE_4__*) ; 
 float fz_rasterizer_graphics_min_line_width (TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_6__* push_group_for_separations (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* resolve_color (int /*<<< orphan*/ *,TYPE_5__*,float const*,int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 

__attribute__((used)) static void
fz_draw_stroke_path(fz_context *ctx, fz_device *devp, const fz_path *path, const fz_stroke_state *stroke, fz_matrix in_ctm,
	fz_colorspace *colorspace_in, const float *color, float alpha, fz_color_params color_params)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_matrix ctm = fz_concat(in_ctm, dev->transform);
	fz_rasterizer *rast = dev->rast;
	fz_colorspace *colorspace = fz_default_colorspace(ctx, dev->default_cs, colorspace_in);
	float expansion = fz_matrix_expansion(ctm);
	float flatness;
	float linewidth = stroke->linewidth;
	unsigned char colorbv[FZ_MAX_COLORS + 1];
	fz_irect bbox;
	float aa_level = 2.0f/(fz_rasterizer_graphics_aa_level(rast)+2);
	fz_draw_state *state = &dev->stack[dev->top];
	float mlw = fz_rasterizer_graphics_min_line_width(rast);
	fz_overprint op = { { 0 } };
	fz_overprint *eop;

	if (dev->top == 0 && dev->resolve_spots)
		state = push_group_for_separations(ctx, dev, color_params, dev->default_cs);

	if (mlw > aa_level)
		aa_level = mlw;
	if (expansion < FLT_EPSILON)
		expansion = 1;
	if (linewidth * expansion < aa_level)
		linewidth = aa_level / expansion;
	flatness = 0.3f / expansion;
	if (flatness < 0.001f)
		flatness = 0.001f;

	bbox = fz_intersect_irect(fz_pixmap_bbox_no_ctx(state->dest), state->scissor);
	if (fz_flatten_stroke_path(ctx, rast, path, stroke, ctm, flatness, linewidth, &bbox, &bbox))
		return;

	if (state->blendmode & FZ_BLEND_KNOCKOUT)
		state = fz_knockout_begin(ctx, dev);

	eop = resolve_color(ctx, &op, color, colorspace, alpha, color_params, colorbv, state->dest);

#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top, "");
	fz_dump_blend(ctx, "Before stroke ", state->dest);
	if (state->shape)
		fz_dump_blend(ctx, "/S=", state->shape);
	if (state->group_alpha)
		fz_dump_blend(ctx, "/GA=", state->group_alpha);
	printf("\n");
#endif
	fz_convert_rasterizer(ctx, rast, 0, state->dest, colorbv, eop);
	if (state->shape)
	{
		if (!rast->fns.reusable)
			(void)fz_flatten_stroke_path(ctx, rast, path, stroke, ctm, flatness, linewidth, &bbox, NULL);

		colorbv[0] = 255;
		fz_convert_rasterizer(ctx, rast, 0, state->shape, colorbv, 0);
	}
	if (state->group_alpha)
	{
		if (!rast->fns.reusable)
			(void)fz_flatten_stroke_path(ctx, rast, path, stroke, ctm, flatness, linewidth, &bbox, NULL);

		colorbv[0] = 255 * alpha;
		fz_convert_rasterizer(ctx, rast, 0, state->group_alpha, colorbv, 0);
	}

#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top, "");
	fz_dump_blend(ctx, "After stroke ", state->dest);
	if (state->shape)
		fz_dump_blend(ctx, "/S=", state->shape);
	if (state->group_alpha)
		fz_dump_blend(ctx, "/GA=", state->group_alpha);
	printf("\n");
#endif

	if (state->blendmode & FZ_BLEND_KNOCKOUT)
		fz_knockout_end(ctx, dev);
}