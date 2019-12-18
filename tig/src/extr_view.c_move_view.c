#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lineno; int offset; } ;
struct view {int lines; int height; int /*<<< orphan*/  win; TYPE_2__ pos; int /*<<< orphan*/ * line; TYPE_1__* ops; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_3__ {int /*<<< orphan*/  (* select ) (struct view*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ABS (int) ; 
#define  REQ_MOVE_DOWN 139 
#define  REQ_MOVE_FIRST_LINE 138 
#define  REQ_MOVE_HALF_PAGE_DOWN 137 
#define  REQ_MOVE_HALF_PAGE_UP 136 
#define  REQ_MOVE_LAST_LINE 135 
#define  REQ_MOVE_PAGE_DOWN 134 
#define  REQ_MOVE_PAGE_UP 133 
#define  REQ_MOVE_UP 132 
#define  REQ_MOVE_WHEEL_DOWN 131 
#define  REQ_MOVE_WHEEL_UP 130 
#define  REQ_NEXT 129 
#define  REQ_PREVIOUS 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  do_scroll_view (struct view*,int) ; 
 int /*<<< orphan*/  draw_view_line (struct view*,size_t) ; 
 int opt_mouse_scroll ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  report_clear () ; 
 int /*<<< orphan*/  stub1 (struct view*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  view_is_displayed (struct view*) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 

void
move_view(struct view *view, enum request request)
{
	int scroll_steps = 0;
	int steps;

	switch (request) {
	case REQ_MOVE_FIRST_LINE:
		steps = -view->pos.lineno;
		break;

	case REQ_MOVE_LAST_LINE:
		steps = view->lines - view->pos.lineno - 1;
		break;

	case REQ_MOVE_PAGE_UP:
		steps = view->height > view->pos.lineno
		      ? -view->pos.lineno : -view->height;
		break;

	case REQ_MOVE_PAGE_DOWN:
		steps = view->pos.lineno + view->height >= view->lines
		      ? view->lines - view->pos.lineno - 1 : view->height;
		break;

	case REQ_MOVE_HALF_PAGE_UP:
		steps = view->height / 2 > view->pos.lineno
		      ? -view->pos.lineno : -(view->height / 2);
		break;

	case REQ_MOVE_HALF_PAGE_DOWN:
		steps = view->pos.lineno + view->height / 2 >= view->lines
		      ? view->lines - view->pos.lineno - 1 : view->height / 2;
		break;

	case REQ_MOVE_WHEEL_DOWN:
		steps = opt_mouse_scroll;
		break;

	case REQ_MOVE_WHEEL_UP:
		steps = -opt_mouse_scroll;
		break;

	case REQ_MOVE_UP:
	case REQ_PREVIOUS:
		steps = -1;
		break;

	case REQ_MOVE_DOWN:
	case REQ_NEXT:
		steps = 1;
		break;

	default:
		die("request %d not handled in switch", request);
	}

	if (steps <= 0 && view->pos.lineno == 0) {
		report("Cannot move beyond the first line");
		return;

	} else if (steps >= 0 && view->pos.lineno + 1 >= view->lines) {
		report("Cannot move beyond the last line");
		return;
	}

	/* Move the current line */
	view->pos.lineno += steps;
	assert(0 <= view->pos.lineno && view->pos.lineno < view->lines);

	/* Check whether the view needs to be scrolled */
	if (view->pos.lineno < view->pos.offset ||
	    view->pos.lineno >= view->pos.offset + view->height) {
		scroll_steps = steps;
		if (steps < 0 && -steps > view->pos.offset) {
			scroll_steps = -view->pos.offset;

		} else if (steps > 0) {
			if (view->pos.lineno == view->lines - 1 &&
			    view->lines > view->height) {
				scroll_steps = view->lines - view->pos.offset - 1;
				if (scroll_steps >= view->height)
					scroll_steps -= view->height - 1;
			}
		}
	}

	if (!view_is_displayed(view)) {
		view->pos.offset += scroll_steps;
		assert(0 <= view->pos.offset && view->pos.offset < view->lines);
		view->ops->select(view, &view->line[view->pos.lineno]);
		return;
	}

	/* Repaint the old "current" line if we be scrolling */
	if (ABS(steps) < view->height)
		draw_view_line(view, view->pos.lineno - steps - view->pos.offset);

	if (scroll_steps) {
		do_scroll_view(view, scroll_steps);
		return;
	}

	/* Draw the current line */
	draw_view_line(view, view->pos.lineno - view->pos.offset);

	wnoutrefresh(view->win);
	report_clear();
}