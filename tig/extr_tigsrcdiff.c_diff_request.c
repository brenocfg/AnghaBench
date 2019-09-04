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
struct view {int /*<<< orphan*/  vid; } ;
struct line {int dummy; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
#define  REQ_EDIT 131 
#define  REQ_ENTER 130 
 int REQ_NONE ; 
#define  REQ_REFRESH 129 
#define  REQ_VIEW_BLAME 128 
 int diff_common_edit (struct view*,int,struct line*) ; 
 int diff_common_enter (struct view*,int,struct line*) ; 
 int diff_trace_origin (struct view*,struct line*) ; 
 int pager_request (struct view*,int,struct line*) ; 
 int /*<<< orphan*/  refresh_view (struct view*) ; 
 int /*<<< orphan*/  reload_view (struct view*) ; 
 int /*<<< orphan*/  string_rev_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum request
diff_request(struct view *view, enum request request, struct line *line)
{
	switch (request) {
	case REQ_VIEW_BLAME:
		return diff_trace_origin(view, line);

	case REQ_EDIT:
		return diff_common_edit(view, request, line);

	case REQ_ENTER:
		return diff_common_enter(view, request, line);

	case REQ_REFRESH:
		if (string_rev_is_null(view->vid))
			refresh_view(view);
		else
			reload_view(view);
		return REQ_NONE;

	default:
		return pager_request(view, request, line);
	}
}