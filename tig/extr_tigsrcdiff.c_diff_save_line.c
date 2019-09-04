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
struct TYPE_2__ {size_t lineno; } ;
struct view {TYPE_1__ pos; struct line* line; } ;
struct line {int dummy; } ;
struct diff_state {TYPE_1__ pos; int /*<<< orphan*/  lineno; int /*<<< orphan*/  file; } ;
typedef  enum open_flags { ____Placeholder_open_flags } open_flags ;

/* Variables and functions */
 int OPEN_RELOAD ; 
 int /*<<< orphan*/  diff_get_lineno (struct view*,struct line*) ; 
 char* diff_get_pathname (struct view*,struct line*) ; 
 int /*<<< orphan*/  get_path (char const*) ; 
 scalar_t__ view_has_line (struct view*,struct line*) ; 

void
diff_save_line(struct view *view, struct diff_state *state, enum open_flags flags)
{
	if (flags & OPEN_RELOAD) {
		struct line *line = &view->line[view->pos.lineno];
		const char *file = view_has_line(view, line) ? diff_get_pathname(view, line) : NULL;

		if (file) {
			state->file = get_path(file);
			state->lineno = diff_get_lineno(view, line);
			state->pos = view->pos;
		}
	}
}