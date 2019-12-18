#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct view {scalar_t__ parent; int /*<<< orphan*/  lines; struct stage_state* private; } ;
struct stage_state {int /*<<< orphan*/  diff; } ;
struct buffer {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DEFAULT ; 
 scalar_t__ LINE_STAT_UNTRACKED ; 
 scalar_t__ diff_common_read (struct view*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_done_highlight (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_restore_line (struct view*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maximize_view (scalar_t__,int) ; 
 int /*<<< orphan*/  opt_diff_highlight ; 
 int pager_common_read (struct view*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pager_read (struct view*,struct buffer*,int) ; 
 int /*<<< orphan*/  report (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stage_line_type ; 

__attribute__((used)) static bool
stage_read(struct view *view, struct buffer *buf, bool force_stop)
{
	struct stage_state *state = view->private;

	if (stage_line_type == LINE_STAT_UNTRACKED)
		return pager_common_read(view, buf ? buf->data : NULL, LINE_DEFAULT, NULL);

	if (!buf) {
		if (!diff_done_highlight(&state->diff)) {
			report("Failed run the diff-highlight program: %s", opt_diff_highlight);
			return true;
		}
	}

	if (!buf && !view->lines && view->parent) {
		maximize_view(view->parent, true);
		return true;
	}

	if (!buf)
		diff_restore_line(view, &state->diff);

	if (buf && diff_common_read(view, buf->data, &state->diff))
		return true;

	return pager_read(view, buf, force_stop);
}