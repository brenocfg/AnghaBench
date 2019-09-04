#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int graph; } ;
struct TYPE_5__ {TYPE_1__ commit_title; } ;
struct view_column {TYPE_2__ opt; } ;
struct view {TYPE_3__* env; struct main_state* private; } ;
struct rev_flags {int /*<<< orphan*/  search_offset; int /*<<< orphan*/  with_graph; scalar_t__ with_reflog; int /*<<< orphan*/  member_0; } ;
struct main_state {int with_graph; int first_parent; } ;
struct TYPE_6__ {int /*<<< orphan*/ * search; } ;

/* Variables and functions */
 scalar_t__ COMMIT_ORDER_REVERSE ; 
 int /*<<< orphan*/  VIEW_COLUMN_COMMIT_TITLE ; 
 int /*<<< orphan*/  argv_append (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  argv_parse_rev_flag (char const*,struct rev_flags*) ; 
 struct view_column* get_view_column (struct view*,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_commit_order ; 
 int /*<<< orphan*/  opt_diff_options ; 
 int /*<<< orphan*/  opt_rev_args ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static bool
main_check_argv(struct view *view, const char *argv[])
{
	struct main_state *state = view->private;
	bool with_reflog = false;
	int i;

	for (i = 0; argv[i]; i++) {
		const char *arg = argv[i];
		struct rev_flags rev_flags = {0};

		if (!strcmp(arg, "--graph")) {
			struct view_column *column = get_view_column(view, VIEW_COLUMN_COMMIT_TITLE);

			if (column) {
				column->opt.commit_title.graph = true;
				if (opt_commit_order != COMMIT_ORDER_REVERSE)
					state->with_graph = true;
			}
			argv[i] = "";
			continue;
		}

		if (!strcmp(arg, "--merge")) {
			argv_append(&opt_rev_args, "--boundary");
			continue;
		}

		if (!strcmp(arg, "--first-parent")) {
			state->first_parent = true;
			argv_append(&opt_diff_options, arg);
		}

		if (!argv_parse_rev_flag(arg, &rev_flags))
			continue;

		if (rev_flags.with_reflog)
			with_reflog = true;
		if (!rev_flags.with_graph)
			state->with_graph = false;
		arg += rev_flags.search_offset;
		if (*arg && !*view->env->search)
			string_ncopy(view->env->search, arg, strlen(arg));
	}

	return with_reflog;
}