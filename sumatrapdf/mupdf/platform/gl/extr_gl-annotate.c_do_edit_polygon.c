#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ fz_point ;
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_9__ {scalar_t__ active; int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ down; scalar_t__ right; int /*<<< orphan*/  cursor; scalar_t__ hot; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_CURSOR_CROSSHAIR ; 
 int /*<<< orphan*/  GL_LINE_STRIP ; 
 int /*<<< orphan*/  GL_POINTS ; 
 int /*<<< orphan*/  ctx ; 
 TYPE_1__ fz_transform_point (TYPE_1__,int /*<<< orphan*/ ) ; 
 TYPE_1__ fz_transform_point_xy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor4f (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glPointSize (int) ; 
 int /*<<< orphan*/  glVertex2f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_add_annot_vertex (int /*<<< orphan*/ ,scalar_t__,TYPE_1__) ; 
 TYPE_1__ pdf_annot_vertex (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int pdf_annot_vertex_count (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ selected_annot ; 
 TYPE_2__ ui ; 
 scalar_t__ ui_mouse_inside (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  view_page_area ; 
 int /*<<< orphan*/  view_page_ctm ; 
 int /*<<< orphan*/  view_page_inv_ctm ; 

__attribute__((used)) static void do_edit_polygon(fz_irect canvas_area, int close)
{
	static int drawing = 0;
	fz_point a, p;

	if (ui_mouse_inside(canvas_area) && ui_mouse_inside(view_page_area))
	{
		ui.hot = selected_annot;
		if (!ui.active || ui.active == selected_annot)
			ui.cursor = GLUT_CURSOR_CROSSHAIR;
		if (!ui.active && ui.down)
		{
			ui.active = selected_annot;
			drawing = 1;
		}
	}

	if (ui.active == selected_annot && drawing)
	{
		int n = pdf_annot_vertex_count(ctx, selected_annot);
		if (n > 0)
		{
			p = pdf_annot_vertex(ctx, selected_annot, n-1);
			p = fz_transform_point(p, view_page_ctm);
			if (close)
			{
				a = pdf_annot_vertex(ctx, selected_annot, 0);
				a = fz_transform_point(a, view_page_ctm);
			}
			glBegin(GL_LINE_STRIP);
			glColor4f(1, 0, 0, 1);
			glVertex2f(p.x, p.y);
			glVertex2f(ui.x, ui.y);
			if (close)
				glVertex2f(a.x, a.y);
			glEnd();
		}

		glColor4f(1, 0, 0, 1);
		glPointSize(4);
		glBegin(GL_POINTS);
		glVertex2f(ui.x, ui.y);
		glEnd();

		/* cancel on right click */
		if (ui.right)
			drawing = 0;

		/* commit point on mouse-up */
		if (!ui.down)
		{
			fz_point p = fz_transform_point_xy(ui.x, ui.y, view_page_inv_ctm);
			pdf_add_annot_vertex(ctx, selected_annot, p);
			drawing = 0;
		}
	}
}