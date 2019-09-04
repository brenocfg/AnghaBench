#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int offset; int /*<<< orphan*/  col; } ;
struct view {int height; int lines; TYPE_1__ pos; int /*<<< orphan*/  width; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
#define  REQ_SCROLL_FIRST_COL 136 
#define  REQ_SCROLL_LEFT 135 
#define  REQ_SCROLL_LINE_DOWN 134 
#define  REQ_SCROLL_LINE_UP 133 
#define  REQ_SCROLL_PAGE_DOWN 132 
#define  REQ_SCROLL_PAGE_UP 131 
#define  REQ_SCROLL_RIGHT 130 
#define  REQ_SCROLL_WHEEL_DOWN 129 
#define  REQ_SCROLL_WHEEL_UP 128 
 int /*<<< orphan*/  apply_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  do_scroll_view (struct view*,int) ; 
 int /*<<< orphan*/  opt_horizontal_scroll ; 
 int opt_mouse_scroll ; 
 int /*<<< orphan*/  redraw_view (struct view*) ; 
 int /*<<< orphan*/  redraw_view_from (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  report_clear () ; 
 int /*<<< orphan*/  view_is_displayed (struct view*) ; 

void
scroll_view(struct view *view, enum request request)
{
	int lines = 1;

	assert(view_is_displayed(view));

	if (request == REQ_SCROLL_WHEEL_DOWN || request == REQ_SCROLL_WHEEL_UP)
		lines = opt_mouse_scroll;

	switch (request) {
	case REQ_SCROLL_FIRST_COL:
		view->pos.col = 0;
		redraw_view_from(view, 0);
		report_clear();
		return;
	case REQ_SCROLL_LEFT:
		if (view->pos.col == 0) {
			report("Cannot scroll beyond the first column");
			return;
		}
		if (view->pos.col <= apply_step(opt_horizontal_scroll, view->width))
			view->pos.col = 0;
		else
			view->pos.col -= apply_step(opt_horizontal_scroll, view->width);
		redraw_view_from(view, 0);
		report_clear();
		return;
	case REQ_SCROLL_RIGHT:
		view->pos.col += apply_step(opt_horizontal_scroll, view->width);
		redraw_view(view);
		report_clear();
		return;
	case REQ_SCROLL_PAGE_DOWN:
		lines = view->height;
		/* Fall-through */
	case REQ_SCROLL_WHEEL_DOWN:
	case REQ_SCROLL_LINE_DOWN:
		if (view->pos.offset + lines > view->lines)
			lines = view->lines - view->pos.offset;

		if (lines == 0 || view->pos.offset + view->height >= view->lines) {
			report("Cannot scroll beyond the last line");
			return;
		}
		break;

	case REQ_SCROLL_PAGE_UP:
		lines = view->height;
		/* Fall-through */
	case REQ_SCROLL_LINE_UP:
	case REQ_SCROLL_WHEEL_UP:
		if (lines > view->pos.offset)
			lines = view->pos.offset;

		if (lines == 0) {
			report("Cannot scroll beyond the first line");
			return;
		}

		lines = -lines;
		break;

	default:
		die("request %d not handled in switch", request);
	}

	do_scroll_view(view, lines);
}