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
struct reference {struct ref* ref; } ;
struct ref {char* name; } ;
struct line {struct reference* data; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_3__ {int /*<<< orphan*/  argv; int /*<<< orphan*/  env; } ;

/* Variables and functions */
 char const* GIT_MAIN_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OPEN_PREPARED ; 
 int OPEN_SPLIT ; 
#define  REQ_ENTER 129 
 int REQ_NONE ; 
#define  REQ_REFRESH 128 
 int /*<<< orphan*/  argv_format (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**,int,int) ; 
 int /*<<< orphan*/  commit_order_arg () ; 
 int /*<<< orphan*/  encoding_arg ; 
 int /*<<< orphan*/  load_refs (int) ; 
 int /*<<< orphan*/  log_custom_pretty_arg () ; 
 TYPE_1__ main_view ; 
 int /*<<< orphan*/  open_view (struct view*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  refresh_view (struct view*) ; 
 int /*<<< orphan*/  refs_is_all (struct reference*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  show_notes_arg () ; 

__attribute__((used)) static enum request
refs_request(struct view *view, enum request request, struct line *line)
{
	struct reference *reference = line->data;

	switch (request) {
	case REQ_REFRESH:
		load_refs(true);
		refresh_view(view);
		return REQ_NONE;

	case REQ_ENTER:
	{
		const struct ref *ref = reference->ref;
		const char *all_references_argv[] = {
			GIT_MAIN_LOG(encoding_arg, commit_order_arg(),
				"%(mainargs)", "",
				refs_is_all(reference) ? "--all" : ref->name, "",
				show_notes_arg(), log_custom_pretty_arg())
		};

		if (!argv_format(main_view.env, &main_view.argv, all_references_argv, false, false))
			report("Failed to format argument");
		else
			open_view(view, &main_view, OPEN_SPLIT | OPEN_PREPARED);
		return REQ_NONE;
	}
	default:
		return request;
	}
}