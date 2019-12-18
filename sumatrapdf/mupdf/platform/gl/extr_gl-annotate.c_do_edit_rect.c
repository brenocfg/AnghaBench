#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {float x0; float x1; float y0; float y1; } ;
typedef  TYPE_1__ fz_rect ;
struct TYPE_16__ {scalar_t__ x0; int x1; scalar_t__ y0; int y1; } ;
typedef  TYPE_2__ fz_irect ;
struct TYPE_17__ {scalar_t__ active; scalar_t__ x; scalar_t__ y; int down_x; int down_y; scalar_t__ down; scalar_t__ right; scalar_t__ hot; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 TYPE_2__ fz_expand_irect (TYPE_2__,int) ; 
 TYPE_1__ fz_transform_rect (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_set_annot_rect (int /*<<< orphan*/ ,scalar_t__,TYPE_1__) ; 
 scalar_t__ rects_differ (TYPE_1__,TYPE_1__,int) ; 
 scalar_t__ selected_annot ; 
 TYPE_4__ ui ; 
 scalar_t__ ui_mouse_inside (TYPE_2__) ; 
 int /*<<< orphan*/  view_page_inv_ctm ; 

__attribute__((used)) static void do_edit_rect(fz_irect canvas_area, fz_irect area, fz_rect *rect)
{
	enum {
		ER_N=1, ER_E=2, ER_S=4, ER_W=8,
		ER_NONE = 0,
		ER_NW = ER_N|ER_W,
		ER_NE = ER_N|ER_E,
		ER_SW = ER_S|ER_W,
		ER_SE = ER_S|ER_E,
		ER_MOVE = ER_N|ER_E|ER_S|ER_W,
	};
	static fz_rect start_rect;
	static int state = ER_NONE;

	area = fz_expand_irect(area, 5);
	if (ui_mouse_inside(canvas_area) && ui_mouse_inside(area))
	{
		ui.hot = selected_annot;
		if (!ui.active && ui.down)
		{
			ui.active = selected_annot;
			start_rect = *rect;
			state = ER_NONE;
			if (ui.x <= area.x0 + 10) state |= ER_W;
			if (ui.x >= area.x1 - 10) state |= ER_E;
			if (ui.y <= area.y0 + 10) state |= ER_N;
			if (ui.y >= area.y1 - 10) state |= ER_S;
			if (!state) state = ER_MOVE;
		}
	}

	if (ui.active == selected_annot && state != ER_NONE)
	{
		*rect = start_rect;
		if (state & ER_W) rect->x0 += (ui.x - ui.down_x);
		if (state & ER_E) rect->x1 += (ui.x - ui.down_x);
		if (state & ER_N) rect->y0 += (ui.y - ui.down_y);
		if (state & ER_S) rect->y1 += (ui.y - ui.down_y);
		if (rect->x1 < rect->x0) { float t = rect->x1; rect->x1 = rect->x0; rect->x0 = t; }
		if (rect->y1 < rect->y0) { float t = rect->y1; rect->y1 = rect->y0; rect->y0 = t; }
		if (rect->x1 < rect->x0 + 10) rect->x1 = rect->x0 + 10;
		if (rect->y1 < rect->y0 + 10) rect->y1 = rect->y0 + 10;

		/* cancel on right click */
		if (ui.right)
			state = ER_NONE;

		/* commit on mouse-up */
		if (!ui.down)
		{
			state = ER_NONE;
			if (rects_differ(start_rect, *rect, 1))
			{
				fz_rect trect = fz_transform_rect(*rect, view_page_inv_ctm);
				pdf_set_annot_rect(ctx, selected_annot, trect);
			}
		}
	}
}