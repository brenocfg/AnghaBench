#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_9__ ;
typedef  struct TYPE_51__   TYPE_8__ ;
typedef  struct TYPE_50__   TYPE_7__ ;
typedef  struct TYPE_49__   TYPE_6__ ;
typedef  struct TYPE_48__   TYPE_5__ ;
typedef  struct TYPE_47__   TYPE_4__ ;
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_2__ ;
typedef  struct TYPE_44__   TYPE_1__ ;
typedef  struct TYPE_43__   TYPE_14__ ;
typedef  struct TYPE_42__   TYPE_11__ ;
typedef  struct TYPE_41__   TYPE_10__ ;

/* Type definitions */
struct TYPE_50__ {scalar_t__ f; scalar_t__ e; int /*<<< orphan*/  d; scalar_t__ c; scalar_t__ b; int /*<<< orphan*/  a; } ;
struct TYPE_46__ {int len; int /*<<< orphan*/  font; TYPE_2__* items; TYPE_7__ trm; struct TYPE_46__* next; } ;
typedef  TYPE_3__ fz_text_span ;
struct TYPE_47__ {TYPE_3__* head; } ;
typedef  TYPE_4__ fz_text ;
typedef  int /*<<< orphan*/  fz_rasterizer ;
struct TYPE_48__ {int n; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  TYPE_5__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_path ;
struct TYPE_44__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_49__ {TYPE_1__ member_0; } ;
typedef  TYPE_6__ fz_overprint ;
typedef  TYPE_7__ fz_matrix ;
struct TYPE_51__ {TYPE_5__* pixmap; } ;
typedef  TYPE_8__ fz_glyph ;
struct TYPE_52__ {int blendmode; TYPE_14__* group_alpha; TYPE_14__* shape; int /*<<< orphan*/  scissor; TYPE_14__* dest; } ;
typedef  TYPE_9__ fz_draw_state ;
struct TYPE_41__ {size_t top; int /*<<< orphan*/  default_cs; scalar_t__ resolve_spots; int /*<<< orphan*/ * rast; TYPE_9__* stack; TYPE_7__ transform; } ;
typedef  TYPE_10__ fz_draw_device ;
struct TYPE_42__ {int hints; int flags; } ;
typedef  TYPE_11__ fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;
struct TYPE_45__ {int gid; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_43__ {int /*<<< orphan*/  alpha; int /*<<< orphan*/ * colorspace; } ;

/* Variables and functions */
 int FZ_BLEND_KNOCKOUT ; 
 int FZ_DEVFLAG_GRIDFIT_AS_TILED ; 
 int FZ_DONT_INTERPOLATE_IMAGES ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  FZ_MAX_COLORS ; 
 int /*<<< orphan*/  draw_glyph (unsigned char*,TYPE_14__*,TYPE_8__*,int,int,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int floorf (scalar_t__) ; 
 TYPE_7__ fz_concat (TYPE_7__,TYPE_7__) ; 
 int /*<<< orphan*/ * fz_default_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_draw_fill_path (int /*<<< orphan*/ *,TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__,int /*<<< orphan*/ *,float const*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_glyph (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  fz_drop_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_9__* fz_knockout_begin (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/  fz_knockout_end (int /*<<< orphan*/ *,TYPE_10__*) ; 
 int /*<<< orphan*/ * fz_outline_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_7__) ; 
 int /*<<< orphan*/  fz_paint_image (int /*<<< orphan*/ *,TYPE_14__*,int /*<<< orphan*/ *,TYPE_14__*,TYPE_14__*,TYPE_5__*,TYPE_7__,float,int,int,TYPE_6__*) ; 
 int /*<<< orphan*/  fz_rasterizer_text_aa_level (int /*<<< orphan*/ *) ; 
 TYPE_8__* fz_render_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_9__* push_group_for_separations (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* resolve_color (int /*<<< orphan*/ *,TYPE_6__*,float const*,int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,unsigned char*,TYPE_14__*) ; 

__attribute__((used)) static void
fz_draw_fill_text(fz_context *ctx, fz_device *devp, const fz_text *text, fz_matrix in_ctm,
	fz_colorspace *colorspace_in, const float *color, float alpha, fz_color_params color_params)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_matrix ctm = fz_concat(in_ctm, dev->transform);
	fz_draw_state *state = &dev->stack[dev->top];
	fz_colorspace *model = state->dest->colorspace;
	unsigned char colorbv[FZ_MAX_COLORS + 1];
	unsigned char shapebv, shapebva;
	fz_text_span *span;
	int i;
	fz_colorspace *colorspace = NULL;
	fz_rasterizer *rast = dev->rast;
	fz_overprint op = { { 0 } };
	fz_overprint *eop;

	if (dev->top == 0 && dev->resolve_spots)
		state = push_group_for_separations(ctx, dev, color_params, dev->default_cs);

	if (colorspace_in)
		colorspace = fz_default_colorspace(ctx, dev->default_cs, colorspace_in);

	if (colorspace == NULL && model != NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "color destination requires source color");

	if (state->blendmode & FZ_BLEND_KNOCKOUT)
		state = fz_knockout_begin(ctx, dev);

	eop = resolve_color(ctx, &op, color, colorspace, alpha, color_params, colorbv, state->dest);
	shapebv = 255;
	shapebva = 255 * alpha;

	for (span = text->head; span; span = span->next)
	{
		fz_matrix tm, trm;
		fz_glyph *glyph;
		int gid;

		tm = span->trm;

		for (i = 0; i < span->len; i++)
		{
			gid = span->items[i].gid;
			if (gid < 0)
				continue;

			tm.e = span->items[i].x;
			tm.f = span->items[i].y;
			trm = fz_concat(tm, ctm);

			glyph = fz_render_glyph(ctx, span->font, gid, &trm, model, &state->scissor, state->dest->alpha, fz_rasterizer_text_aa_level(rast));
			if (glyph)
			{
				fz_pixmap *pixmap = glyph->pixmap;
				int x = floorf(trm.e);
				int y = floorf(trm.f);
				if (pixmap == NULL || pixmap->n == 1)
				{
					draw_glyph(colorbv, state->dest, glyph, x, y, &state->scissor, eop);
					if (state->shape)
						draw_glyph(&shapebv, state->shape, glyph, x, y, &state->scissor, 0);
					if (state->group_alpha)
						draw_glyph(&shapebva, state->group_alpha, glyph, x, y, &state->scissor, 0);
				}
				else
				{
					fz_matrix mat;
					mat.a = pixmap->w; mat.b = mat.c = 0; mat.d = pixmap->h;
					mat.e = x + pixmap->x; mat.f = y + pixmap->y;
					fz_paint_image(ctx, state->dest, &state->scissor, state->shape, state->group_alpha, pixmap, mat, alpha * 255, !(devp->hints & FZ_DONT_INTERPOLATE_IMAGES), devp->flags & FZ_DEVFLAG_GRIDFIT_AS_TILED, eop);
				}
				fz_drop_glyph(ctx, glyph);
			}
			else
			{
				fz_path *path = fz_outline_glyph(ctx, span->font, gid, tm);
				if (path)
				{
					fz_draw_fill_path(ctx, devp, path, 0, in_ctm, colorspace, color, alpha, color_params);
					fz_drop_path(ctx, path);
				}
				else
				{
					fz_warn(ctx, "cannot render glyph");
				}
			}
		}
	}

	if (state->blendmode & FZ_BLEND_KNOCKOUT)
		fz_knockout_end(ctx, dev);
}