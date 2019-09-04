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
struct view {TYPE_1__* env; int /*<<< orphan*/  ref; } ;
struct ref {int dummy; } ;
struct line {scalar_t__ type; struct commit* data; } ;
struct commit {int /*<<< orphan*/  id; int /*<<< orphan*/  title; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ LINE_STAT_STAGED ; 
 scalar_t__ LINE_STAT_UNSTAGED ; 
 scalar_t__ LINE_STAT_UNTRACKED ; 
 struct ref* main_get_commit_refs (struct line*,struct commit*) ; 
 int /*<<< orphan*/  ref_update_env (TYPE_1__*,struct ref const*,int) ; 
 int /*<<< orphan*/  status_stage_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
main_select(struct view *view, struct line *line)
{
	struct commit *commit = line->data;

	if (line->type == LINE_STAT_STAGED || line->type == LINE_STAT_UNSTAGED || line->type == LINE_STAT_UNTRACKED) {
		string_ncopy(view->ref, commit->title, strlen(commit->title));
		status_stage_info(view->env->status, line->type, NULL);
	} else {
		const struct ref *ref = main_get_commit_refs(line, commit);

		string_copy_rev(view->ref, commit->id);
		if (ref)
			ref_update_env(view->env, ref, true);
	}
	string_copy_rev(view->env->commit, commit->id);
}