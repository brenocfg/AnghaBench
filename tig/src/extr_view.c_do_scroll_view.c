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
struct TYPE_2__ {scalar_t__ offset; scalar_t__ lineno; } ;
struct view {scalar_t__ lines; int height; int has_scrolled; int /*<<< orphan*/  win; TYPE_1__ pos; } ;

/* Variables and functions */
 int ABS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ draw_view_line (struct view*,int) ; 
 int /*<<< orphan*/  redraw_view (struct view*) ; 
 int /*<<< orphan*/  report_clear () ; 
 int /*<<< orphan*/  scrollok (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wscrl (int /*<<< orphan*/ ,int) ; 

void
do_scroll_view(struct view *view, int lines)
{
	bool redraw_current_line = false;

	/* The rendering expects the new offset. */
	view->pos.offset += lines;

	assert(0 <= view->pos.offset && view->pos.offset < view->lines);
	assert(lines);

	/* Move current line into the view. */
	if (view->pos.lineno < view->pos.offset) {
		view->pos.lineno = view->pos.offset;
		redraw_current_line = true;
	} else if (view->pos.lineno >= view->pos.offset + view->height) {
		view->pos.lineno = view->pos.offset + view->height - 1;
		redraw_current_line = true;
	}

	assert(view->pos.offset <= view->pos.lineno && view->pos.lineno < view->lines);

	/* Redraw the whole screen if scrolling is pointless. */
	if (view->height < ABS(lines)) {
		redraw_view(view);

	} else {
		int line = lines > 0 ? view->height - lines : 0;
		int end = line + ABS(lines);

		scrollok(view->win, true);
		wscrl(view->win, lines);
		scrollok(view->win, false);

		while (line < end && draw_view_line(view, line))
			line++;

		if (redraw_current_line)
			draw_view_line(view, view->pos.lineno - view->pos.offset);
		wnoutrefresh(view->win);
	}

	view->has_scrolled = true;
	report_clear();
}