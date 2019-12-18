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
struct TYPE_2__ {scalar_t__ lineno; scalar_t__ offset; } ;
struct view {scalar_t__ height; TYPE_1__ pos; struct view* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPEN_RELOAD ; 
 int /*<<< orphan*/  VIEW_FLEX_WIDTH ; 
 int current_view ; 
 struct view** display ; 
 int displayed_views () ; 
 int /*<<< orphan*/  do_scroll_view (struct view*,int) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  load_view (struct view*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_focus_child ; 
 int /*<<< orphan*/  opt_vertical_split ; 
 int /*<<< orphan*/  resize_display () ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  update_view_title (struct view*) ; 
 int vertical_split_is_enabled (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ view_has_flags (struct view*,int /*<<< orphan*/ ) ; 
 scalar_t__ view_is_displayed (struct view*) ; 

void
split_view(struct view *prev, struct view *view)
{
	int height, width;
	bool vsplit;
	int nviews = displayed_views();

	getmaxyx(stdscr, height, width);
	vsplit = vertical_split_is_enabled(opt_vertical_split, height, width);

	display[1] = view;
	current_view = opt_focus_child ? 1 : 0;
	view->parent = prev;
	resize_display();

	if (prev->pos.lineno - prev->pos.offset >= prev->height) {
		/* Take the title line into account. */
		int lines = prev->pos.lineno - prev->pos.offset - prev->height + 1;

		/* Scroll the view that was split if the current line is
		 * outside the new limited view. */
		do_scroll_view(prev, lines);
	}

	if (view != prev && view_is_displayed(prev)) {
		/* "Blur" the previous view. */
		update_view_title(prev);
	}

	if (view_has_flags(prev, VIEW_FLEX_WIDTH) && vsplit && nviews == 1)
		load_view(prev, NULL, OPEN_RELOAD);
}