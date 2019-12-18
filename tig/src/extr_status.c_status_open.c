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
struct view {int /*<<< orphan*/  watch; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
struct TYPE_2__ {scalar_t__* worktree; scalar_t__ is_inside_work_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_HEADER ; 
 int /*<<< orphan*/  LINE_STAT_STAGED ; 
 int /*<<< orphan*/  LINE_STAT_UNSTAGED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  WATCH_INDEX ; 
 int /*<<< orphan*/  add_line_nodata (struct view*,int /*<<< orphan*/ ) ; 
 int error (char*) ; 
 scalar_t__ is_initial_commit () ; 
 TYPE_1__ repo ; 
 int /*<<< orphan*/  reset_view (struct view*) ; 
 int /*<<< orphan*/  show_untracked_only ; 
 char const** status_diff_files_argv ; 
 char const** status_diff_index_argv ; 
 char const** status_list_no_head_argv ; 
 int /*<<< orphan*/  status_read_untracked (struct view*) ; 
 int /*<<< orphan*/  status_restore (struct view*) ; 
 int /*<<< orphan*/  status_run (struct view*,char const**,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_update_onbranch () ; 
 int /*<<< orphan*/  update_index () ; 
 int /*<<< orphan*/  watch_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum status_code
status_open(struct view *view, enum open_flags flags)
{
	const char **staged_argv = is_initial_commit() ?
		status_list_no_head_argv : status_diff_index_argv;
	char staged_status = staged_argv == status_list_no_head_argv ? 'A' : 0;

	if (!(repo.is_inside_work_tree || *repo.worktree))
		return error("The status view requires a working tree");

	reset_view(view);

	/* FIXME: Watch untracked files and on-branch info. */
	watch_register(&view->watch, WATCH_INDEX);

	add_line_nodata(view, LINE_HEADER);
	status_update_onbranch();

	update_index();

	if ((!show_untracked_only && !status_run(view, staged_argv, staged_status, LINE_STAT_STAGED)) ||
	    (!show_untracked_only && !status_run(view, status_diff_files_argv, 0, LINE_STAT_UNSTAGED)) ||
	    !status_read_untracked(view))
		return error("Failed to load status data");

	/* Restore the exact position or use the specialized restore
	 * mode? */
	status_restore(view);
	return SUCCESS;
}