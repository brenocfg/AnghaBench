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
struct line {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 scalar_t__ LINE_COMMIT ; 
 int /*<<< orphan*/  VIEW_NO_REF ; 
 char* box_text (struct line*) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_copy_rev_from_commit_line (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  view_has_flags (struct view*,int /*<<< orphan*/ ) ; 

void
pager_select(struct view *view, struct line *line)
{
	const char *text = box_text(line);

	string_ncopy(view->env->text, text, strlen(text));

	if (line->type == LINE_COMMIT) {
		string_copy_rev_from_commit_line(view->env->commit, text);
		if (!view_has_flags(view, VIEW_NO_REF))
			string_copy_rev(view->ref, view->env->commit);
	}
}