#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xps_resource ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_paint_visual_brush ; 
 int /*<<< orphan*/  xps_parse_tiling_brush (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_resolve_resource_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int /*<<< orphan*/ **,char**) ; 

void
xps_parse_visual_brush(fz_context *ctx, xps_document *doc, fz_matrix ctm, fz_rect area,
	char *base_uri, xps_resource *dict, fz_xml *root)
{
	fz_xml *node;

	char *visual_uri;
	char *visual_att;
	fz_xml *visual_tag = NULL;

	visual_att = fz_xml_att(root, "Visual");

	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
	{
		if (fz_xml_is_tag(node, "VisualBrush.Visual"))
			visual_tag = fz_xml_down(node);
	}

	visual_uri = base_uri;
	xps_resolve_resource_reference(ctx, doc, dict, &visual_att, &visual_tag, &visual_uri);

	if (visual_tag)
	{
		xps_parse_tiling_brush(ctx, doc, ctm, area,
			visual_uri, dict, root, xps_paint_visual_brush, visual_tag);
	}
}