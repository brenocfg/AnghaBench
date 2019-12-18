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
typedef  int /*<<< orphan*/  svg_state ;
typedef  int /*<<< orphan*/  svg_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svg_run_circle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_ellipse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_g (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_polygon (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_polyline (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_rect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_svg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svg_run_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_run_text_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_run_text_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_run_text_span (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svg_run_use (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
svg_run_element(fz_context *ctx, fz_device *dev, svg_document *doc, fz_xml *root, const svg_state *state)
{
	if (fz_xml_is_tag(root, "svg"))
		svg_run_svg(ctx, dev, doc, root, state);

	else if (fz_xml_is_tag(root, "g"))
		svg_run_g(ctx, dev, doc, root, state);

	else if (fz_xml_is_tag(root, "title"))
		;
	else if (fz_xml_is_tag(root, "desc"))
		;

	else if (fz_xml_is_tag(root, "defs"))
		;
	else if (fz_xml_is_tag(root, "symbol"))
		;

	else if (fz_xml_is_tag(root, "use"))
		svg_run_use(ctx, dev, doc, root, state);

	else if (fz_xml_is_tag(root, "path"))
		svg_run_path(ctx, dev, doc, root, state);
	else if (fz_xml_is_tag(root, "rect"))
		svg_run_rect(ctx, dev, doc, root, state);
	else if (fz_xml_is_tag(root, "circle"))
		svg_run_circle(ctx, dev, doc, root, state);
	else if (fz_xml_is_tag(root, "ellipse"))
		svg_run_ellipse(ctx, dev, doc, root, state);
	else if (fz_xml_is_tag(root, "line"))
		svg_run_line(ctx, dev, doc, root, state);
	else if (fz_xml_is_tag(root, "polyline"))
		svg_run_polyline(ctx, dev, doc, root, state);
	else if (fz_xml_is_tag(root, "polygon"))
		svg_run_polygon(ctx, dev, doc, root, state);

	else if (fz_xml_is_tag(root, "image"))
		svg_run_image(ctx, dev, doc, root, state);

#if 0
	else if (fz_xml_is_tag(root, "text"))
		svg_run_text(ctx, dev, doc, root);
	else if (fz_xml_is_tag(root, "tspan"))
		svg_run_text_span(ctx, dev, doc, root);
	else if (fz_xml_is_tag(root, "tref"))
		svg_run_text_ref(ctx, dev, doc, root);
	else if (fz_xml_is_tag(root, "textPath"))
		svg_run_text_path(ctx, dev, doc, root);
#endif

	else
	{
		/* ignore unrecognized tags */
	}
}