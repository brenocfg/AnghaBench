#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int y0; int y1; scalar_t__ x0; scalar_t__ x1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct list {int scroll_y; int is_tree; int item_y; TYPE_1__ area; } ;
typedef  TYPE_1__ fz_irect ;
struct TYPE_7__ {int lineheight; int middle_y; int y; int scroll_y; int window_h; struct list* hot; struct list* active; scalar_t__ middle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 int /*<<< orphan*/  UI_COLOR_TEXT_BG ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glScissor (scalar_t__,int,scalar_t__,int) ; 
 TYPE_5__ ui ; 
 int /*<<< orphan*/  ui_draw_bevel_rect (TYPE_1__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ui_mouse_inside (TYPE_1__) ; 
 TYPE_1__ ui_pack (int,int) ; 
 int /*<<< orphan*/  ui_scrollbar (scalar_t__,int,scalar_t__,int,int*,int,int) ; 

void ui_tree_begin(struct list *list, int count, int req_w, int req_h, int is_tree)
{
	static int start_scroll_y = 0; /* we can only drag in one list at a time, so static is safe */

	fz_irect outer_area = ui_pack(req_w, req_h);
	fz_irect area = { outer_area.x0+2, outer_area.y0+2, outer_area.x1-2, outer_area.y1-2 };

	int max_scroll_y = count * ui.lineheight - (area.y1-area.y0);

	if (max_scroll_y > 0)
		area.x1 -= 16;

	if (ui_mouse_inside(area))
	{
		ui.hot = list;
		if (!ui.active && ui.middle)
		{
			ui.active = list;
			start_scroll_y = list->scroll_y;
		}
	}

	/* middle button dragging */
	if (ui.active == list)
		list->scroll_y = start_scroll_y + (ui.middle_y - ui.y) * 5;

	/* scroll wheel events */
	if (ui.hot == list)
		list->scroll_y -= ui.scroll_y * ui.lineheight * 3;

	/* clamp scrolling to client area */
	if (list->scroll_y >= max_scroll_y)
		list->scroll_y = max_scroll_y;
	if (list->scroll_y < 0)
		list->scroll_y = 0;

	ui_draw_bevel_rect(outer_area, UI_COLOR_TEXT_BG, 1);
	if (max_scroll_y > 0)
	{
		ui_scrollbar(area.x1, area.y0, area.x1+16, area.y1,
				&list->scroll_y, area.y1-area.y0, count * ui.lineheight);
	}

	list->is_tree = is_tree;
	list->area = area;
	list->item_y = area.y0 - list->scroll_y;

	glScissor(list->area.x0, ui.window_h-list->area.y1, list->area.x1-list->area.x0, list->area.y1-list->area.y0);
	glEnable(GL_SCISSOR_TEST);
}