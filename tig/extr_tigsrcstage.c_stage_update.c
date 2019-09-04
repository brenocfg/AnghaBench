#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct view {int dummy; } ;
struct line {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DIFF_CHUNK ; 
 scalar_t__ LINE_STAT_UNTRACKED ; 
 struct line* find_prev_line_by_type (struct view*,struct line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_initial_commit () ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  stage_apply_chunk (struct view*,struct line*,struct line*,int) ; 
 scalar_t__ stage_line_type ; 
 TYPE_1__ stage_status ; 
 int /*<<< orphan*/  stage_update_files (struct view*,scalar_t__) ; 
 int /*<<< orphan*/  status_update_file (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static bool
stage_update(struct view *view, struct line *line, bool single)
{
	struct line *chunk = NULL;

	if (!is_initial_commit() && stage_line_type != LINE_STAT_UNTRACKED)
		chunk = find_prev_line_by_type(view, line, LINE_DIFF_CHUNK);

	if (chunk) {
		if (!stage_apply_chunk(view, chunk, single ? line : NULL, false)) {
			report("Failed to apply chunk");
			return false;
		}

	} else if (!stage_status.status) {
		if (!stage_update_files(view, stage_line_type)) {
			report("Failed to update files");
			return false;
		}

	} else if (!status_update_file(&stage_status, stage_line_type)) {
		report("Failed to update file");
		return false;
	}

	return true;
}