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
struct view {int /*<<< orphan*/  argv; TYPE_1__* env; int /*<<< orphan*/  ref; } ;
struct line {int dummy; } ;
typedef  enum request { ____Placeholder_request } request ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
struct TYPE_2__ {int /*<<< orphan*/  stash; } ;

/* Variables and functions */
 char* DIFF_ARGS ; 
 int OPEN_DEFAULT ; 
 int OPEN_PREPARED ; 
 int OPEN_SPLIT ; 
#define  REQ_ENTER 129 
 int REQ_NONE ; 
#define  REQ_VIEW_DIFF 128 
 int /*<<< orphan*/  argv_format (TYPE_1__*,int /*<<< orphan*/ *,char const**,int,int) ; 
 char* diff_context_arg () ; 
 struct view diff_view ; 
 struct view** display ; 
 char* encoding_arg ; 
 char* ignore_space_arg () ; 
 int main_request (struct view*,int,struct line*) ; 
 int /*<<< orphan*/  maximize_view (struct view*,int) ; 
 int /*<<< orphan*/  open_view (struct view*,struct view*,int) ; 
 int /*<<< orphan*/  report (char*) ; 
 char* show_notes_arg () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ view_is_displayed (struct view*) ; 

enum request
stash_request(struct view *view, enum request request, struct line *line)
{
	enum open_flags flags = (view_is_displayed(view) && request != REQ_VIEW_DIFF)
				? OPEN_SPLIT : OPEN_DEFAULT;
	struct view *diff = &diff_view;

	switch (request) {
	case REQ_VIEW_DIFF:
	case REQ_ENTER:
		if (view_is_displayed(view) && display[0] != view)
			maximize_view(view, true);

		if (!view_is_displayed(diff) ||
		    strcmp(view->env->stash, diff->ref)) {
			const char *diff_argv[] = {
				"git", "stash", "show", encoding_arg, "--pretty=fuller",
					"--root", "--patch-with-stat",
					show_notes_arg(), diff_context_arg(),
					ignore_space_arg(), DIFF_ARGS,
					"--no-color", "%(stash)", NULL
			};

			if (!argv_format(diff_view.env, &diff_view.argv, diff_argv, false, false))
				report("Failed to format argument");
			else
				open_view(view, &diff_view, flags | OPEN_PREPARED);
		}
		return REQ_NONE;

	default:
		return main_request(view, request, line);
	}
}