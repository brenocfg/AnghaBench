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
struct position {scalar_t__ offset; size_t lineno; } ;
struct view {struct position pos; int /*<<< orphan*/ * line; TYPE_1__* ops; int /*<<< orphan*/  win; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* select ) (struct view*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  draw_view_line (struct view*,size_t) ; 
 scalar_t__ goto_view_line (struct view*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  redraw_view (struct view*) ; 
 int /*<<< orphan*/  stub1 (struct view*,int /*<<< orphan*/ *) ; 
 scalar_t__ view_is_displayed (struct view*) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 

void
select_view_line(struct view *view, unsigned long lineno)
{
	struct position old = view->pos;

	if (goto_view_line(view, view->pos.offset, lineno)) {
		if (view_is_displayed(view)) {
			if (old.offset != view->pos.offset) {
				redraw_view(view);
			} else {
				draw_view_line(view, old.lineno - view->pos.offset);
				draw_view_line(view, view->pos.lineno - view->pos.offset);
				wnoutrefresh(view->win);
			}
		} else {
			view->ops->select(view, &view->line[view->pos.lineno]);
		}
	}
}