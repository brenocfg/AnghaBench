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
struct main_state {int /*<<< orphan*/  add_changes_untracked; int /*<<< orphan*/  add_changes_staged; int /*<<< orphan*/  add_changes_unstaged; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_STAT_STAGED ; 
 int /*<<< orphan*/  LINE_STAT_UNSTAGED ; 
 int /*<<< orphan*/  LINE_STAT_UNTRACKED ; 
 char* NULL_ID ; 
 scalar_t__ main_add_changes_commit (struct view*,int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static bool
main_add_changes(struct view *view, struct main_state *state, const char *parent)
{
	const char *staged_parent = parent;
	const char *unstaged_parent = NULL_ID;
	const char *untracked_parent = NULL_ID;

	if (!state->add_changes_staged) {
		staged_parent = NULL;
		unstaged_parent = parent;
	}

	if (!state->add_changes_unstaged) {
		unstaged_parent = NULL;
		if (!state->add_changes_staged)
			untracked_parent = parent;
	}

	if (!state->add_changes_untracked) {
		untracked_parent = NULL;
	}

	return main_add_changes_commit(view, LINE_STAT_UNTRACKED, untracked_parent, "Untracked changes")
	    && main_add_changes_commit(view, LINE_STAT_UNSTAGED, unstaged_parent, "Unstaged changes")
	    && main_add_changes_commit(view, LINE_STAT_STAGED, staged_parent, "Staged changes");
}