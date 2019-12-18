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
struct view {int /*<<< orphan*/  ref; TYPE_1__* env; struct log_state* private; } ;
struct log_state {int last_lineno; scalar_t__ last_type; } ;
struct line {int lineno; scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit; } ;

/* Variables and functions */
 scalar_t__ LINE_COMMIT ; 
 int /*<<< orphan*/  VIEW_NO_REF ; 
 int abs (int) ; 
 struct line* find_prev_line_by_type (struct view*,struct line*,scalar_t__) ; 
 int /*<<< orphan*/  log_copy_rev (struct view*,struct line*) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  view_has_flags (struct view*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
log_select(struct view *view, struct line *line)
{
	struct log_state *state = view->private;
	int last_lineno = state->last_lineno;

	if (!last_lineno || abs(last_lineno - line->lineno) > 1
	    || (state->last_type == LINE_COMMIT && last_lineno > line->lineno)) {
		struct line *commit_line = find_prev_line_by_type(view, line, LINE_COMMIT);

		if (commit_line)
			log_copy_rev(view, commit_line);
	}

	if (line->type == LINE_COMMIT && !view_has_flags(view, VIEW_NO_REF))
		log_copy_rev(view, line);
	string_copy_rev(view->env->commit, view->ref);
	state->last_lineno = line->lineno;
	state->last_type = line->type;
}