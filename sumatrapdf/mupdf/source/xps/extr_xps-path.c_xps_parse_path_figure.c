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
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_closepath (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_lineto (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,float) ; 
 int /*<<< orphan*/  fz_moveto (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,float) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 scalar_t__ fz_xml_is_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  xps_parse_arc_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  xps_parse_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float*,float*) ; 
 int /*<<< orphan*/  xps_parse_poly_bezier_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  xps_parse_poly_line_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  xps_parse_poly_quadratic_bezier_segment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void
xps_parse_path_figure(fz_context *ctx, xps_document *doc, fz_path *path, fz_xml *root, int stroking)
{
	fz_xml *node;

	char *is_closed_att;
	char *start_point_att;
	char *is_filled_att;

	int is_closed = 0;
	int is_filled = 1;
	float start_x = 0;
	float start_y = 0;

	int skipped_stroke = 0;

	is_closed_att = fz_xml_att(root, "IsClosed");
	start_point_att = fz_xml_att(root, "StartPoint");
	is_filled_att = fz_xml_att(root, "IsFilled");

	if (is_closed_att)
		is_closed = !strcmp(is_closed_att, "true");
	if (is_filled_att)
		is_filled = !strcmp(is_filled_att, "true");
	if (start_point_att)
		xps_parse_point(ctx, doc, start_point_att, &start_x, &start_y);

	if (!stroking && !is_filled) /* not filled, when filling */
		return;

	fz_moveto(ctx, path, start_x, start_y);

	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
	{
		if (fz_xml_is_tag(node, "ArcSegment"))
			xps_parse_arc_segment(ctx, doc, path, node, stroking, &skipped_stroke);
		if (fz_xml_is_tag(node, "PolyBezierSegment"))
			xps_parse_poly_bezier_segment(ctx, doc, path, node, stroking, &skipped_stroke);
		if (fz_xml_is_tag(node, "PolyLineSegment"))
			xps_parse_poly_line_segment(ctx, doc, path, node, stroking, &skipped_stroke);
		if (fz_xml_is_tag(node, "PolyQuadraticBezierSegment"))
			xps_parse_poly_quadratic_bezier_segment(ctx, doc, path, node, stroking, &skipped_stroke);
	}

	if (is_closed)
	{
		if (stroking && skipped_stroke)
			fz_lineto(ctx, path, start_x, start_y); /* we've skipped using fz_moveto... */
		else
			fz_closepath(ctx, path); /* no skipped segments, safe to closepath properly */
	}
}