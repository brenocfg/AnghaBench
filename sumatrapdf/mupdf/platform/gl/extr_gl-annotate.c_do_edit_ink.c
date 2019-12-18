#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* y; void* x; } ;
typedef  TYPE_1__ fz_point ;
struct TYPE_12__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x1; int /*<<< orphan*/  x0; } ;
typedef  TYPE_2__ fz_irect ;
struct TYPE_13__ {scalar_t__ active; int x; int y; scalar_t__ down; scalar_t__ right; int /*<<< orphan*/  cursor; scalar_t__ hot; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLUT_CURSOR_CROSSHAIR ; 
 int /*<<< orphan*/  GL_LINE_STRIP ; 
 int INT_MIN ; 
 int /*<<< orphan*/  ctx ; 
 void* fz_clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fz_transform_point (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColor4f (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glVertex2f (void*,void*) ; 
 scalar_t__ nelem (TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_add_annot_ink_list (int /*<<< orphan*/ ,scalar_t__,int,TYPE_1__*) ; 
 scalar_t__ selected_annot ; 
 TYPE_5__ ui ; 
 scalar_t__ ui_mouse_inside (TYPE_2__) ; 
 TYPE_2__ view_page_area ; 
 int /*<<< orphan*/  view_page_inv_ctm ; 

__attribute__((used)) static void do_edit_ink(fz_irect canvas_area)
{
	static int drawing = 0;
	static fz_point p[1000];
	static int n, last_x, last_y;
	int i;

	if (ui_mouse_inside(canvas_area) && ui_mouse_inside(view_page_area))
	{
		ui.hot = selected_annot;
		if (!ui.active || ui.active == selected_annot)
			ui.cursor = GLUT_CURSOR_CROSSHAIR;
		if (!ui.active && ui.down)
		{
			ui.active = selected_annot;
			drawing = 1;
			n = 0;
			last_x = INT_MIN;
			last_y = INT_MIN;
		}
	}

	if (ui.active == selected_annot && drawing)
	{
		if (n < (int)nelem(p) && (ui.x != last_x || ui.y != last_y))
		{
			p[n].x = fz_clamp(ui.x, view_page_area.x0, view_page_area.x1);
			p[n].y = fz_clamp(ui.y, view_page_area.y0, view_page_area.y1);
			++n;
		}
		last_x = ui.x;
		last_y = ui.y;

		if (n > 1)
		{
			glBegin(GL_LINE_STRIP);
			glColor4f(1, 0, 0, 1);
			for (i = 0; i < n; ++i)
				glVertex2f(p[i].x, p[i].y);
			glEnd();
		}

		/* cancel on right click */
		if (ui.right)
		{
			drawing = 0;
			n = 0;
		}

		/* commit stroke on mouse-up */
		if (!ui.down)
		{
			if (n > 1)
			{
				for (i = 0; i < n; ++i)
					p[i] = fz_transform_point(p[i], view_page_inv_ctm);
				pdf_add_annot_ink_list(ctx, selected_annot, n, p);
			}
			drawing = 0;
			n = 0;
		}
	}
}