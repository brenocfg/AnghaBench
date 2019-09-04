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
struct view {unsigned long lines; struct line* line; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct status {TYPE_1__ new; int /*<<< orphan*/  status; } ;
struct line {int type; struct status* data; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int /*<<< orphan*/  refresh_view (struct view*) ; 
 int /*<<< orphan*/  select_view_line (struct view*,unsigned long) ; 
 int /*<<< orphan*/  status_restore (struct view*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
status_exists(struct view *view, struct status *status, enum line_type type)
{
	unsigned long lineno;

	refresh_view(view);

	for (lineno = 0; lineno < view->lines; lineno++) {
		struct line *line = &view->line[lineno];
		struct status *pos = line->data;

		if (line->type != type)
			continue;
		if ((!pos && (!status || !status->status) && line[1].data) ||
		    (pos && status && !strcmp(status->new.name, pos->new.name))) {
			select_view_line(view, lineno);
			status_restore(view);
			return true;
		}
	}

	return false;
}