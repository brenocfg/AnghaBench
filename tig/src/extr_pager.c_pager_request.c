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
struct view {int dummy; } ;
struct line {scalar_t__ type; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 scalar_t__ LINE_COMMIT ; 
 int /*<<< orphan*/  OPEN_SPLIT ; 
 int REQ_ENTER ; 
 int REQ_NONE ; 
 int /*<<< orphan*/  REQ_SCROLL_LINE_DOWN ; 
 int /*<<< orphan*/  VIEW_OPEN_DIFF ; 
 size_t current_view ; 
 struct view** display ; 
 int /*<<< orphan*/  open_diff_view (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scroll_view (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_view_title (struct view*) ; 
 scalar_t__ view_has_flags (struct view*,int /*<<< orphan*/ ) ; 

enum request
pager_request(struct view *view, enum request request, struct line *line)
{
	int split = 0;

	if (request != REQ_ENTER)
		return request;

	if (line->type == LINE_COMMIT && view_has_flags(view, VIEW_OPEN_DIFF)) {
		open_diff_view(view, OPEN_SPLIT);
		split = 1;
	}

	/* Always scroll the view even if it was split. That way
	 * you can use Enter to scroll through the log view and
	 * split open each commit diff. */
	if (view == display[current_view])
		scroll_view(view, REQ_SCROLL_LINE_DOWN);

	/* FIXME: A minor workaround. Scrolling the view will call report_clear()
	 * but if we are scrolling a non-current view this won't properly
	 * update the view title. */
	if (split)
		update_view_title(view);

	return REQ_NONE;
}