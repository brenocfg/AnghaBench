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
typedef  int time_t ;
struct view {scalar_t__ lines; int start_time; int update_secs; int force_redraw; int /*<<< orphan*/  pipe; TYPE_1__* ops; struct encoding* encoding; } ;
struct encoding {int dummy; } ;
struct buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct view*,struct buffer*,int) ;} ;

/* Variables and functions */
 struct encoding* default_encoding ; 
 int /*<<< orphan*/  encoding_convert (struct encoding*,struct buffer*) ; 
 int /*<<< orphan*/  end_update (struct view*,int) ; 
 int /*<<< orphan*/  io_can_read (int /*<<< orphan*/ ,int) ; 
 scalar_t__ io_eof (int /*<<< orphan*/ ) ; 
 scalar_t__ io_error (int /*<<< orphan*/ ) ; 
 scalar_t__ io_get (int /*<<< orphan*/ ,struct buffer*,char,int) ; 
 int /*<<< orphan*/  io_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redraw_view (struct view*) ; 
 int /*<<< orphan*/  redraw_view_dirty (struct view*) ; 
 int /*<<< orphan*/  redraw_view_from (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report (char*,...) ; 
 scalar_t__ restore_view_position (struct view*) ; 
 int /*<<< orphan*/  stub1 (struct view*,struct buffer*,int) ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_view_title (struct view*) ; 
 scalar_t__ view_is_displayed (struct view*) ; 

bool
update_view(struct view *view)
{
	/* Clear the view and redraw everything since the tree sorting
	 * might have rearranged things. */
	bool redraw = view->lines == 0;
	bool can_read = true;
	struct encoding *encoding = view->encoding ? view->encoding : default_encoding;
	struct buffer line;

	if (!view->pipe)
		return true;

	if (!io_can_read(view->pipe, false)) {
		if (view->lines == 0 && view_is_displayed(view)) {
			time_t secs = time(NULL) - view->start_time;

			if (secs > 1 && secs > view->update_secs) {
				if (view->update_secs == 0)
					redraw_view(view);
				update_view_title(view);
				view->update_secs = secs;
			}
		}
		return true;
	}

	for (; io_get(view->pipe, &line, '\n', can_read); can_read = false) {
		if (encoding && !encoding_convert(encoding, &line)) {
			report("Encoding failure");
			end_update(view, true);
			return false;
		}

		if (!view->ops->read(view, &line, false)) {
			report("Allocation failure");
			end_update(view, true);
			return false;
		}
	}

	if (io_error(view->pipe)) {
		report("Failed to read: %s", io_strerror(view->pipe));
		end_update(view, true);

	} else if (io_eof(view->pipe)) {
		end_update(view, false);
	}

	if (restore_view_position(view))
		redraw = true;

	if (!view_is_displayed(view))
		return true;

	if (redraw || view->force_redraw)
		redraw_view_from(view, 0);
	else
		redraw_view_dirty(view);
	view->force_redraw = false;

	/* Update the title _after_ the redraw so that if the redraw picks up a
	 * commit reference in view->ref it'll be available here. */
	update_view_title(view);
	return true;
}