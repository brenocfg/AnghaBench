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
struct view {int /*<<< orphan*/  private; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;

/* Variables and functions */
 char* DIFF_ARGS ; 
 int SUCCESS ; 
 int begin_update (struct view*,int /*<<< orphan*/ *,char const**,int) ; 
 char* diff_context_arg () ; 
 int diff_init_highlight (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_save_line (struct view*,int /*<<< orphan*/ ,int) ; 
 char* encoding_arg ; 
 char* ignore_space_arg () ; 
 char* show_notes_arg () ; 
 char* use_mailmap_arg () ; 

__attribute__((used)) static enum status_code
diff_open(struct view *view, enum open_flags flags)
{
	const char *diff_argv[] = {
		"git", "show", encoding_arg, "--pretty=fuller", "--root",
			"--patch-with-stat", use_mailmap_arg(),
			show_notes_arg(), diff_context_arg(), ignore_space_arg(),
			DIFF_ARGS, "%(cmdlineargs)", "--no-color", "%(commit)",
			"--", "%(fileargs)", NULL
	};
	enum status_code code;

	diff_save_line(view, view->private, flags);

	code = begin_update(view, NULL, diff_argv, flags);
	if (code != SUCCESS)
		return code;

	return diff_init_highlight(view, view->private);
}