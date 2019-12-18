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
struct view {int line; } ;
struct line {scalar_t__ type; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 scalar_t__ LINE_DIFF_STAT ; 
 int REQ_NONE ; 
 struct line* diff_find_header_from_stat (struct view*,struct line*) ; 
 int pager_request (struct view*,int,struct line*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  report_clear () ; 
 int /*<<< orphan*/  select_view_line (struct view*,struct line*) ; 

enum request
diff_common_enter(struct view *view, enum request request, struct line *line)
{
	if (line->type == LINE_DIFF_STAT) {
		line = diff_find_header_from_stat(view, line);
		if (!line) {
			report("Failed to find file diff");
			return REQ_NONE;
		}

		select_view_line(view, line - view->line);
		report_clear();
		return REQ_NONE;

	} else {
		return pager_request(view, request, line);
	}
}