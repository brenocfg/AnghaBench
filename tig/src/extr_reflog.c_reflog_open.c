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
struct view {int /*<<< orphan*/  watch; struct main_state* private; } ;
struct main_state {int with_graph; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;

/* Variables and functions */
 int WATCH_HEAD ; 
 int WATCH_REFS ; 
 int begin_update (struct view*,int /*<<< orphan*/ *,char const**,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 char* encoding_arg ; 
 scalar_t__ is_initial_view (struct view*) ; 
 scalar_t__ opt_file_args ; 
 int /*<<< orphan*/  watch_register (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static enum status_code
reflog_open(struct view *view, enum open_flags flags)
{
	struct main_state *state = view->private;
	const char *reflog_argv[] = {
		"git", "reflog", "show", encoding_arg, "%(cmdlineargs)",
			"%(revargs)", "--no-color", "--pretty=raw", NULL
	};

	if (is_initial_view(view) && opt_file_args)
		die("No revisions match the given arguments.");

	state->with_graph = false;
	watch_register(&view->watch, WATCH_HEAD | WATCH_REFS);
	return begin_update(view, NULL, reflog_argv, flags);
}