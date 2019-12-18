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
struct view {int /*<<< orphan*/  ref; int /*<<< orphan*/  pipe; } ;
struct line {struct blame* data; } ;
struct blame {TYPE_1__* commit; } ;
typedef  enum request { ____Placeholder_request } request ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;
struct TYPE_2__ {int /*<<< orphan*/ * parent_id; int /*<<< orphan*/  filename; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 char const* GIT_DIFF_BLAME (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* GIT_DIFF_BLAME_NO_PARENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_ID ; 
 int OPEN_DEFAULT ; 
 int OPEN_SPLIT ; 
#define  REQ_BACK 131 
#define  REQ_ENTER 130 
 int REQ_NONE ; 
#define  REQ_PARENT 129 
#define  REQ_VIEW_BLAME 128 
 int /*<<< orphan*/  blame_go_back (struct view*) ; 
 int /*<<< orphan*/  blame_go_forward (struct view*,struct blame*,int) ; 
 int /*<<< orphan*/  check_blame_commit (struct blame*,int) ; 
 int /*<<< orphan*/  diff_context_arg () ; 
 struct view diff_view ; 
 int /*<<< orphan*/  encoding_arg ; 
 int /*<<< orphan*/  ignore_space_arg () ; 
 int /*<<< orphan*/  open_argv (struct view*,struct view*,char const**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  open_diff_view (struct view*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_rev_is_null (int /*<<< orphan*/ ) ; 
 scalar_t__ view_is_displayed (struct view*) ; 

__attribute__((used)) static enum request
blame_request(struct view *view, enum request request, struct line *line)
{
	enum open_flags flags = view_is_displayed(view) ? OPEN_SPLIT : OPEN_DEFAULT;
	struct blame *blame = line->data;
	struct view *diff = &diff_view;

	switch (request) {
	case REQ_VIEW_BLAME:
	case REQ_PARENT:
		if (!check_blame_commit(blame, request == REQ_VIEW_BLAME))
			break;
		blame_go_forward(view, blame, request == REQ_PARENT);
		break;

	case REQ_BACK:
		blame_go_back(view);
		break;

	case REQ_ENTER:
		if (!check_blame_commit(blame, false))
			break;

		if (view_is_displayed(diff) &&
		    !strcmp(blame->commit->id, diff->ref))
			break;

		if (string_rev_is_null(blame->commit->id)) {
			const char *diff_parent_argv[] = {
				GIT_DIFF_BLAME(encoding_arg,
					diff_context_arg(),
					ignore_space_arg(),
					blame->commit->filename)
			};
			const char *diff_no_parent_argv[] = {
				GIT_DIFF_BLAME_NO_PARENT(encoding_arg,
					diff_context_arg(),
					ignore_space_arg(),
					blame->commit->filename)
			};
			const char **diff_index_argv = *blame->commit->parent_id
				? diff_parent_argv : diff_no_parent_argv;

			open_argv(view, diff, diff_index_argv, NULL, flags);
			if (diff->pipe)
				string_copy_rev(diff->ref, NULL_ID);
		} else {
			open_diff_view(view, flags);
		}
		break;

	default:
		return request;
	}

	return REQ_NONE;
}