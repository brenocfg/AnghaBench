#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  viewbox_h; int /*<<< orphan*/  viewport_h; int /*<<< orphan*/  viewbox_w; int /*<<< orphan*/  viewport_w; } ;
typedef  TYPE_1__ svg_state ;
typedef  int /*<<< orphan*/  svg_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_lex_viewbox (char*,float*,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_parse_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  svg_parse_viewbox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  svg_parse_viewport (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  svg_run_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
svg_run_svg(fz_context *ctx, fz_device *dev, svg_document *doc, fz_xml *root, const svg_state *inherit_state)
{
	svg_state local_state = *inherit_state;
	fz_xml *node;

	char *w_att = fz_xml_att(root, "width");
	char *h_att = fz_xml_att(root, "height");
	char *viewbox_att = fz_xml_att(root, "viewBox");

	/* get default viewport from viewBox if width and/or height is missing */
	if (viewbox_att && (!w_att || !h_att))
	{
		float x, y;
		svg_lex_viewbox(viewbox_att, &x, &y, &local_state.viewbox_w, &local_state.viewbox_h);
		if (!w_att) local_state.viewport_w = local_state.viewbox_w;
		if (!h_att) local_state.viewport_h = local_state.viewbox_h;
	}

	svg_parse_viewport(ctx, doc, root, &local_state);
	svg_parse_viewbox(ctx, doc, root, &local_state);
	svg_parse_common(ctx, doc, root, &local_state);

	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
		svg_run_element(ctx, dev, doc, node, &local_state);
}