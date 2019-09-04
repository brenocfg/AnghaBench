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
struct view {scalar_t__ lines; int /*<<< orphan*/  prev_pos; struct view* prev; int /*<<< orphan*/  win; scalar_t__ pipe; TYPE_1__* ops; scalar_t__ private; int /*<<< orphan*/  watch; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
struct TYPE_2__ {int (* open ) (struct view*,int) ;scalar_t__ private_size; int /*<<< orphan*/  (* done ) (struct view*) ;} ;

/* Variables and functions */
 int OPEN_REFRESH ; 
 int OPEN_RELOAD ; 
 int OPEN_SPLIT ; 
 int SUCCESS ; 
 int /*<<< orphan*/  WATCH_EVENT_SWITCH_VIEW ; 
 scalar_t__ calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  clear_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_update (struct view*,int) ; 
 int /*<<< orphan*/  get_status_message (int) ; 
 int /*<<< orphan*/  maximize_view (struct view*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  redraw_view (struct view*) ; 
 int /*<<< orphan*/  report (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_clear () ; 
 int /*<<< orphan*/  restore_view_position (struct view*) ; 
 int /*<<< orphan*/  split_view (struct view*,struct view*) ; 
 int /*<<< orphan*/  stub1 (struct view*) ; 
 int stub2 (struct view*,int) ; 
 scalar_t__ view_can_refresh (struct view*) ; 
 scalar_t__ view_is_displayed (struct view*) ; 
 int /*<<< orphan*/  view_no_refresh (struct view*,int) ; 
 int watch_dirty (int /*<<< orphan*/ *) ; 
 scalar_t__ watch_update_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 

void
load_view(struct view *view, struct view *prev, enum open_flags flags)
{
	bool refresh = !view_no_refresh(view, flags);

	/* When prev == view it means this is the first loaded view. */
	if (prev && view != prev) {
		view->prev = prev;
	}

	if (!refresh && view_can_refresh(view) &&
	    watch_update_single(&view->watch, WATCH_EVENT_SWITCH_VIEW)) {
		refresh = watch_dirty(&view->watch);
		if (refresh)
			flags |= OPEN_REFRESH;
	}

	if (refresh) {
		enum status_code code;

		if (view->pipe)
			end_update(view, true);
		if (view->ops->private_size) {
			if (!view->private) {
				view->private = calloc(1, view->ops->private_size);
			} else {
				if (view->ops->done)
					view->ops->done(view);
				memset(view->private, 0, view->ops->private_size);
			}
		}

		code = view->ops->open(view, flags);
		if (code != SUCCESS) {
			report("%s", get_status_message(code));
			return;
		}
	}

	if (prev) {
		bool split = !!(flags & OPEN_SPLIT);

		if (split) {
			split_view(prev, view);
		} else {
			maximize_view(view, false);
		}
	}

	restore_view_position(view);

	if (view->pipe && view->lines == 0) {
		/* Clear the old view and let the incremental updating refill
		 * the screen. */
		werase(view->win);
		/* Do not clear the position if it is the first view. */
		if (view->prev && !(flags & (OPEN_RELOAD | OPEN_REFRESH)))
			clear_position(&view->prev_pos);
		report_clear();
	} else if (view_is_displayed(view)) {
		redraw_view(view);
		report_clear();
	}
}