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
struct TYPE_2__ {size_t lineno; } ;
struct view {int /*<<< orphan*/  lines; TYPE_1__ pos; struct line* line; } ;
struct line {int /*<<< orphan*/  type; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report (char*) ; 
 scalar_t__ status_has_none (struct view*,struct line*) ; 
 int /*<<< orphan*/  status_update_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_update_files (struct view*,struct line*) ; 

__attribute__((used)) static bool
status_update(struct view *view)
{
	struct line *line = &view->line[view->pos.lineno];

	assert(view->lines);

	if (!line->data) {
		if (status_has_none(view, line)) {
			report("Nothing to update");
			return false;
		}

		if (!status_update_files(view, line + 1)) {
			report("Failed to update file status");
			return false;
		}

	} else if (!status_update_file(line->data, line->type)) {
		report("Failed to update file status");
		return false;
	}

	return true;
}