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
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DIFF_CHUNK ; 
 scalar_t__ LINE_STAT_UNSTAGED ; 
 struct line* find_prev_line_by_type (struct view*,struct line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_initial_commit () ; 
 int /*<<< orphan*/  prompt_yesno (char*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  stage_apply_chunk (struct view*,struct line*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stage_line_type ; 
 TYPE_1__ stage_status ; 
 int status_revert (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static bool
stage_revert(struct view *view, struct line *line)
{
	struct line *chunk = NULL;

	if (!is_initial_commit() && stage_line_type == LINE_STAT_UNSTAGED)
		chunk = find_prev_line_by_type(view, line, LINE_DIFF_CHUNK);

	if (chunk) {
		if (!prompt_yesno("Are you sure you want to revert changes?"))
			return false;

		if (!stage_apply_chunk(view, chunk, NULL, true)) {
			report("Failed to revert chunk");
			return false;
		}
		return true;

	} else {
		return status_revert(stage_status.status ? &stage_status : NULL,
				     stage_line_type, false);
	}
}