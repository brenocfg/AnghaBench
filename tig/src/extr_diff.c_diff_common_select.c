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
struct view {TYPE_2__* ops; int /*<<< orphan*/  ref; TYPE_1__* env; } ;
struct line {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {scalar_t__* blob; scalar_t__ goto_lineno; scalar_t__ lineno; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 scalar_t__ LINE_DIFF_STAT ; 
 int /*<<< orphan*/  REQ_ENTER ; 
 struct line* diff_find_header_from_stat (struct view*,struct line*) ; 
 scalar_t__ diff_get_lineno (struct view*,struct line*) ; 
 char* diff_get_pathname (struct view*,struct line*) ; 
 char const* get_view_key (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pager_select (struct view*,struct line*) ; 
 int /*<<< orphan*/  string_format (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
diff_common_select(struct view *view, struct line *line, const char *changes_msg)
{
	if (line->type == LINE_DIFF_STAT) {
		struct line *header = diff_find_header_from_stat(view, line);
		if (header) {
			const char *file = diff_get_pathname(view, header);

			if (file) {
				string_format(view->env->file, "%s", file);
				view->env->lineno = view->env->goto_lineno = 0;
				view->env->blob[0] = 0;
			}
		}

		string_format(view->ref, "Press '%s' to jump to file diff",
			      get_view_key(view, REQ_ENTER));
	} else {
		const char *file = diff_get_pathname(view, line);

		if (file) {
			if (changes_msg)
				string_format(view->ref, "%s to '%s'", changes_msg, file);
			string_format(view->env->file, "%s", file);
			view->env->lineno = view->env->goto_lineno = diff_get_lineno(view, line);
			view->env->blob[0] = 0;
		} else {
			string_ncopy(view->ref, view->ops->id, strlen(view->ops->id));
			pager_select(view, line);
		}
	}
}