#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xps_document ;
struct stop {int dummy; } ;
typedef  int /*<<< orphan*/  fz_xml ;
struct TYPE_6__ {float x0; float y0; float x1; float y1; } ;
typedef  TYPE_1__ fz_rect ;
struct TYPE_7__ {float x; float y; } ;
typedef  TYPE_2__ fz_point ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int SPREAD_REFLECT ; 
 int SPREAD_REPEAT ; 
 int ceilf (float) ; 
 int floorf (float) ; 
 int /*<<< orphan*/  fz_invert_matrix (int /*<<< orphan*/ ) ; 
 int fz_maxi (int,int) ; 
 int fz_mini (int,int) ; 
 TYPE_1__ fz_transform_rect (TYPE_1__,int /*<<< orphan*/ ) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xps_draw_one_linear_gradient (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct stop*,int,int,float,float,float,float) ; 
 int /*<<< orphan*/  xps_parse_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float*,float*) ; 

__attribute__((used)) static void
xps_draw_linear_gradient(fz_context *ctx, xps_document *doc, fz_matrix ctm, fz_rect area,
	struct stop *stops, int count,
	fz_xml *root, int spread)
{
	float x0, y0, x1, y1;
	int i, mi, ma;
	float dx, dy, x, y, k;
	fz_point p1, p2;
	fz_matrix inv;

	char *start_point_att = fz_xml_att(root, "StartPoint");
	char *end_point_att = fz_xml_att(root, "EndPoint");

	x0 = y0 = 0;
	x1 = y1 = 1;

	if (start_point_att)
		xps_parse_point(ctx, doc, start_point_att, &x0, &y0);
	if (end_point_att)
		xps_parse_point(ctx, doc, end_point_att, &x1, &y1);

	p1.x = x0; p1.y = y0; p2.x = x1; p2.y = y1;
	inv = fz_invert_matrix(ctm);
	area = fz_transform_rect(area, inv);
	x = p2.x - p1.x; y = p2.y - p1.y;
	k = ((area.x0 - p1.x) * x + (area.y0 - p1.y) * y) / (x * x + y * y);
	mi = floorf(k); ma = ceilf(k);
	k = ((area.x1 - p1.x) * x + (area.y0 - p1.y) * y) / (x * x + y * y);
	mi = fz_mini(mi, floorf(k)); ma = fz_maxi(ma, ceilf(k));
	k = ((area.x0 - p1.x) * x + (area.y1 - p1.y) * y) / (x * x + y * y);
	mi = fz_mini(mi, floorf(k)); ma = fz_maxi(ma, ceilf(k));
	k = ((area.x1 - p1.x) * x + (area.y1 - p1.y) * y) / (x * x + y * y);
	mi = fz_mini(mi, floorf(k)); ma = fz_maxi(ma, ceilf(k));
	dx = x1 - x0; dy = y1 - y0;

	if (spread == SPREAD_REPEAT)
	{
		for (i = mi; i < ma; i++)
			xps_draw_one_linear_gradient(ctx, doc, ctm, stops, count, 0, x0 + i * dx, y0 + i * dy, x1 + i * dx, y1 + i * dy);
	}
	else if (spread == SPREAD_REFLECT)
	{
		if ((mi % 2) != 0)
			mi--;
		for (i = mi; i < ma; i += 2)
		{
			xps_draw_one_linear_gradient(ctx, doc, ctm, stops, count, 0, x0 + i * dx, y0 + i * dy, x1 + i * dx, y1 + i * dy);
			xps_draw_one_linear_gradient(ctx, doc, ctm, stops, count, 0, x0 + (i + 2) * dx, y0 + (i + 2) * dy, x1 + i * dx, y1 + i * dy);
		}
	}
	else
	{
		xps_draw_one_linear_gradient(ctx, doc, ctm, stops, count, 1, x0, y0, x1, y1);
	}
}