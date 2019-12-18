#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct view {int dummy; } ;
struct line {struct commit* data; } ;
struct commit {int /*<<< orphan*/  id; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_3__ {int /*<<< orphan*/  argv; int /*<<< orphan*/  env; } ;

/* Variables and functions */
 char const* GIT_MAIN_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OPEN_PREPARED ; 
 int OPEN_SPLIT ; 
#define  REQ_ENTER 128 
 int REQ_NONE ; 
 int /*<<< orphan*/  argv_format (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**,int,int) ; 
 int /*<<< orphan*/  commit_order_arg () ; 
 int /*<<< orphan*/  encoding_arg ; 
 int /*<<< orphan*/  log_custom_pretty_arg () ; 
 int main_request (struct view*,int,struct line*) ; 
 TYPE_1__ main_view ; 
 int /*<<< orphan*/  open_view (struct view*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  show_notes_arg () ; 

__attribute__((used)) static enum request
reflog_request(struct view *view, enum request request, struct line *line)
{
	struct commit *commit = line->data;

	switch (request) {
	case REQ_ENTER:
	{
		const char *main_argv[] = {
			GIT_MAIN_LOG(encoding_arg, commit_order_arg(),
				"%(mainargs)", "", commit->id, "",
				show_notes_arg(), log_custom_pretty_arg())
		};

		if (!argv_format(main_view.env, &main_view.argv, main_argv, false, false))
			report("Failed to format argument");
		else
			open_view(view, &main_view, OPEN_SPLIT | OPEN_PREPARED);
		return REQ_NONE;
	}

	default:
		return main_request(view, request, line);
	}
}