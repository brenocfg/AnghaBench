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
struct view {int /*<<< orphan*/  line; int /*<<< orphan*/  vid; TYPE_1__* env; struct blob_state* private; } ;
struct line {int dummy; } ;
struct blob_state {int /*<<< orphan*/  file; int /*<<< orphan*/  commit; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {struct line* goto_lineno; int /*<<< orphan*/  ref; int /*<<< orphan*/  file; } ;

/* Variables and functions */
#define  REQ_EDIT 130 
 int REQ_NONE ; 
#define  REQ_REFRESH 129 
#define  REQ_VIEW_BLAME 128 
 int /*<<< orphan*/  open_blob_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pager_request (struct view*,int,struct line*) ; 
 int /*<<< orphan*/  refresh_view (struct view*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum request
blob_request(struct view *view, enum request request, struct line *line)
{
	struct blob_state *state = view->private;

	switch (request) {
	case REQ_REFRESH:
		if (!state->file) {
			report("Cannot reload immutable blob");
		} else {
			string_ncopy(view->env->file, state->file, strlen(state->file));
			refresh_view(view);
		}
		return REQ_NONE;

	case REQ_VIEW_BLAME:
		string_ncopy(view->env->ref, state->commit, strlen(state->commit));
		view->env->goto_lineno = line - view->line;
		return request;

	case REQ_EDIT:
		if (state->file)
			open_editor(state->file, (line - view->line) + 1);
		else
			open_blob_editor(view->vid, NULL, (line - view->line) + 1);
		return REQ_NONE;

	default:
		return pager_request(view, request, line);
	}
}