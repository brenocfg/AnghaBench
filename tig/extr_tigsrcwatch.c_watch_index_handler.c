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
struct watch_handler {int /*<<< orphan*/  last_modified; } ;
struct index_diff {scalar_t__ untracked; scalar_t__ unstaged; scalar_t__ staged; } ;
typedef  enum watch_trigger { ____Placeholder_watch_trigger } watch_trigger ;
typedef  enum watch_event { ____Placeholder_watch_event } watch_event ;
struct TYPE_2__ {int /*<<< orphan*/  git_dir; } ;

/* Variables and functions */
 int WATCH_EVENT_AFTER_COMMAND ; 
 int WATCH_EVENT_SWITCH_VIEW ; 
 int WATCH_INDEX_STAGED ; 
 int WATCH_INDEX_STAGED_NO ; 
 int WATCH_INDEX_STAGED_YES ; 
 int WATCH_INDEX_UNSTAGED ; 
 int WATCH_INDEX_UNSTAGED_NO ; 
 int WATCH_INDEX_UNSTAGED_YES ; 
 int WATCH_INDEX_UNTRACKED ; 
 int WATCH_INDEX_UNTRACKED_NO ; 
 int WATCH_INDEX_UNTRACKED_YES ; 
 int WATCH_NONE ; 
 scalar_t__ check_file_mtime (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_diff (struct index_diff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opt_show_untracked ; 
 TYPE_1__ repo ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum watch_trigger
watch_index_handler(struct watch_handler *handler, enum watch_event event, enum watch_trigger check)
{
	enum watch_trigger changed = WATCH_NONE;
	struct index_diff diff;

	if (event == WATCH_EVENT_AFTER_COMMAND)
		return check_file_mtime(&handler->last_modified, "%s/index", repo.git_dir)
			? check : WATCH_NONE;

	if (!check_file_mtime(&handler->last_modified, "%s/index", repo.git_dir) ||
	    event == WATCH_EVENT_SWITCH_VIEW ||
	    !index_diff(&diff, opt_show_untracked, false))
		return WATCH_NONE;

	if (check & WATCH_INDEX_STAGED) {
		if (diff.staged)
			changed |= WATCH_INDEX_STAGED_YES;
		else
			changed |= WATCH_INDEX_STAGED_NO;
	}

	if (check & WATCH_INDEX_UNSTAGED) {
		if (diff.unstaged)
			changed |= WATCH_INDEX_UNSTAGED_YES;
		else
			changed |= WATCH_INDEX_UNSTAGED_NO;
	}

	if (check & WATCH_INDEX_UNTRACKED) {
		if (diff.untracked)
			changed |= WATCH_INDEX_UNTRACKED_YES;
		else
			changed |= WATCH_INDEX_UNTRACKED_NO;
	}

	if (changed)
		handler->last_modified = time(NULL);

	return changed;
}