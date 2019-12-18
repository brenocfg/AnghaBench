#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_resource ;
struct TYPE_23__ {int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ xps_document ;
struct closure {char* base_uri; void (* func ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;void* user; int /*<<< orphan*/ * root; int /*<<< orphan*/ * dict; } ;
typedef  int /*<<< orphan*/  fz_xml ;
struct TYPE_24__ {float x1; float x0; float y1; float y0; } ;
typedef  TYPE_3__ fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int TILE_FLIP_X ; 
 int TILE_FLIP_X_Y ; 
 int TILE_FLIP_Y ; 
 int TILE_NONE ; 
 int TILE_TILE ; 
 int ceilf (float) ; 
 float fabsf (float) ; 
 int floorf (float) ; 
 int /*<<< orphan*/  fz_begin_tile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__,TYPE_3__,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_end_tile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_invert_matrix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pre_scale (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  fz_pre_translate (int /*<<< orphan*/ ,float,float) ; 
 TYPE_3__ fz_transform_rect (TYPE_3__,int /*<<< orphan*/ ) ; 
 TYPE_3__ fz_unit_rect ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,float,float) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  xps_begin_opacity (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_end_opacity (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_paint_tiling_brush (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__,int,struct closure*) ; 
 TYPE_3__ xps_parse_rectangle (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  xps_parse_transform (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xps_resolve_resource_reference (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void
xps_parse_tiling_brush(fz_context *ctx, xps_document *doc, fz_matrix ctm, fz_rect area,
	char *base_uri, xps_resource *dict, fz_xml *root,
	void (*func)(fz_context *ctx, xps_document*, fz_matrix, fz_rect, char*, xps_resource*, fz_xml*, void*), void *user)
{
	fz_device *dev = doc->dev;
	fz_xml *node;
	struct closure c;

	char *opacity_att;
	char *transform_att;
	char *viewbox_att;
	char *viewport_att;
	char *tile_mode_att;

	fz_xml *transform_tag = NULL;

	fz_rect viewbox;
	fz_rect viewport;
	float xstep, ystep;
	float xscale, yscale;
	int tile_mode;

	opacity_att = fz_xml_att(root, "Opacity");
	transform_att = fz_xml_att(root, "Transform");
	viewbox_att = fz_xml_att(root, "Viewbox");
	viewport_att = fz_xml_att(root, "Viewport");
	tile_mode_att = fz_xml_att(root, "TileMode");

	c.base_uri = base_uri;
	c.dict = dict;
	c.root = root;
	c.user = user;
	c.func = func;

	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
	{
		if (fz_xml_is_tag(node, "ImageBrush.Transform"))
			transform_tag = fz_xml_down(node);
		if (fz_xml_is_tag(node, "VisualBrush.Transform"))
			transform_tag = fz_xml_down(node);
	}

	xps_resolve_resource_reference(ctx, doc, dict, &transform_att, &transform_tag, NULL);

	ctm = xps_parse_transform(ctx, doc, transform_att, transform_tag, ctm);

	viewbox = fz_unit_rect;
	if (viewbox_att)
		viewbox = xps_parse_rectangle(ctx, doc, viewbox_att);

	viewport = fz_unit_rect;
	if (viewport_att)
		viewport = xps_parse_rectangle(ctx, doc, viewport_att);

	if (fabsf(viewport.x1 - viewport.x0) < 0.01f || fabsf(viewport.y1 - viewport.y0) < 0.01f)
		fz_warn(ctx, "not drawing tile for viewport size %.4f x %.4f", viewport.x1 - viewport.x0, viewport.y1 - viewport.y0);
	else if (fabsf(viewbox.x1 - viewbox.x0) < 0.01f || fabsf(viewbox.y1 - viewbox.y0) < 0.01f)
		fz_warn(ctx, "not drawing tile for viewbox size %.4f x %.4f", viewbox.x1 - viewbox.x0, viewbox.y1 - viewbox.y0);

	/* some sanity checks on the viewport/viewbox size */
	if (fabsf(viewport.x1 - viewport.x0) < 0.01f) return;
	if (fabsf(viewport.y1 - viewport.y0) < 0.01f) return;
	if (fabsf(viewbox.x1 - viewbox.x0) < 0.01f) return;
	if (fabsf(viewbox.y1 - viewbox.y0) < 0.01f) return;

	xstep = viewbox.x1 - viewbox.x0;
	ystep = viewbox.y1 - viewbox.y0;

	xscale = (viewport.x1 - viewport.x0) / xstep;
	yscale = (viewport.y1 - viewport.y0) / ystep;

	tile_mode = TILE_NONE;
	if (tile_mode_att)
	{
		if (!strcmp(tile_mode_att, "None"))
			tile_mode = TILE_NONE;
		if (!strcmp(tile_mode_att, "Tile"))
			tile_mode = TILE_TILE;
		if (!strcmp(tile_mode_att, "FlipX"))
			tile_mode = TILE_FLIP_X;
		if (!strcmp(tile_mode_att, "FlipY"))
			tile_mode = TILE_FLIP_Y;
		if (!strcmp(tile_mode_att, "FlipXY"))
			tile_mode = TILE_FLIP_X_Y;
	}

	if (tile_mode == TILE_FLIP_X || tile_mode == TILE_FLIP_X_Y)
		xstep *= 2;
	if (tile_mode == TILE_FLIP_Y || tile_mode == TILE_FLIP_X_Y)
		ystep *= 2;

	xps_begin_opacity(ctx, doc, ctm, area, base_uri, dict, opacity_att, NULL);

	ctm = fz_pre_translate(ctm, viewport.x0, viewport.y0);
	ctm = fz_pre_scale(ctm, xscale, yscale);
	ctm = fz_pre_translate(ctm, -viewbox.x0, -viewbox.y0);

	if (tile_mode != TILE_NONE)
	{
		int x0, y0, x1, y1;
		fz_matrix invctm;
		invctm = fz_invert_matrix(ctm);
		area = fz_transform_rect(area, invctm);
		x0 = floorf(area.x0 / xstep);
		y0 = floorf(area.y0 / ystep);
		x1 = ceilf(area.x1 / xstep);
		y1 = ceilf(area.y1 / ystep);

#ifdef TILE
		if ((x1 - x0) * (y1 - y0) > 1)
#else
		if (0)
#endif
		{
			fz_rect bigview = viewbox;
			bigview.x1 = bigview.x0 + xstep;
			bigview.y1 = bigview.y0 + ystep;
			fz_begin_tile(ctx, dev, area, bigview, xstep, ystep, ctm);
			xps_paint_tiling_brush(ctx, doc, ctm, viewbox, tile_mode, &c);
			fz_end_tile(ctx, dev);
		}
		else
		{
			int x, y;
			for (y = y0; y < y1; y++)
			{
				for (x = x0; x < x1; x++)
				{
					fz_matrix ttm = fz_pre_translate(ctm, xstep * x, ystep * y);
					xps_paint_tiling_brush(ctx, doc, ttm, viewbox, tile_mode, &c);
				}
			}
		}
	}
	else
	{
		xps_paint_tiling_brush(ctx, doc, ctm, viewbox, tile_mode, &c);
	}

	xps_end_opacity(ctx, doc, base_uri, dict, opacity_att, NULL);
}