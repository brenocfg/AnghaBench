#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct view {TYPE_1__* env; int /*<<< orphan*/  pos; struct view* prev; struct view* parent; struct grep_state* private; } ;
struct line {int dummy; } ;
struct grep_state {char const* last_file; } ;
struct grep_line {char const* file; int /*<<< orphan*/  lineno; int /*<<< orphan*/ * text; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_4__ {char const* exec_dir; } ;
struct TYPE_3__ {int /*<<< orphan*/  goto_lineno; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * blob; } ;

/* Variables and functions */
 int OPEN_RELOAD ; 
 int OPEN_SPLIT ; 
#define  REQ_EDIT 131 
#define  REQ_ENTER 130 
 int REQ_NONE ; 
#define  REQ_REFRESH 129 
#define  REQ_VIEW_BLAME 128 
 struct view blob_view ; 
 int /*<<< orphan*/  clear_position (int /*<<< orphan*/ *) ; 
 struct grep_line* grep_get_line (struct line*) ; 
 int /*<<< orphan*/  open_argv (struct view*,struct view*,char const**,char const*,int) ; 
 int /*<<< orphan*/  open_editor (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_view (struct view*) ; 
 TYPE_2__ repo ; 
 int /*<<< orphan*/  select_view_line (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_view_title (struct view*) ; 
 int /*<<< orphan*/  view_is_displayed (struct view*) ; 

__attribute__((used)) static enum request
grep_request(struct view *view, enum request request, struct line *line)
{
	struct grep_state *state = view->private;
	struct grep_line *grep = grep_get_line(line);
	struct view *file_view = &blob_view;

	switch (request) {
	case REQ_REFRESH:
		refresh_view(view);
		return REQ_NONE;

	case REQ_ENTER:
		if (!*grep->file)
			return REQ_NONE;
		if (file_view->parent == view && file_view->prev == view &&
		    state->last_file == grep->file && view_is_displayed(file_view)) {
			if (*grep->text) {
				select_view_line(file_view, grep->lineno);
				update_view_title(file_view);
			}

		} else {
			const char *file_argv[] = { repo.exec_dir, grep->file, NULL };

			clear_position(&file_view->pos);
			view->env->goto_lineno = grep->lineno;
			view->env->blob[0] = 0;
			open_argv(view, file_view, file_argv, repo.exec_dir, OPEN_SPLIT | OPEN_RELOAD);
		}
		state->last_file = grep->file;
		return REQ_NONE;

	case REQ_EDIT:
		if (!*grep->file)
			return request;
		open_editor(grep->file, grep->lineno + 1);
		return REQ_NONE;

	case REQ_VIEW_BLAME:
		view->env->ref[0] = 0;
		view->env->goto_lineno = grep->lineno;
		return request;

	default:
		return request;
	}
}