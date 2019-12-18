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
struct view {scalar_t__ lines; TYPE_1__* env; int /*<<< orphan*/  vid; } ;
struct buffer {size_t size; int /*<<< orphan*/  data; } ;
struct blame_state {int done_reading; } ;
struct blame {scalar_t__* text; int /*<<< orphan*/ * commit; } ;
struct TYPE_4__ {int /*<<< orphan*/  exec_dir; } ;
struct TYPE_3__ {char* ref; char* file; scalar_t__ goto_lineno; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DEFAULT ; 
 int /*<<< orphan*/  OPEN_EXTRA ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  add_line_alloc (struct view*,struct blame**,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ begin_update (struct view*,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 char* encoding_arg ; 
 scalar_t__ failed_to_load_initial_view (struct view*) ; 
 TYPE_2__ repo ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  select_view_line (struct view*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool
blame_read_file(struct view *view, struct buffer *buf, struct blame_state *state)
{
	if (!buf) {
		const char *blame_argv[] = {
			"git", "blame", encoding_arg, "%(blameargs)", "--incremental",
				*view->env->ref ? view->env->ref : "--incremental", "--", view->env->file, NULL
		};

		if (failed_to_load_initial_view(view))
			die("No blame exist for %s", view->vid);

		if (view->lines == 0 || begin_update(view, repo.exec_dir, blame_argv, OPEN_EXTRA) != SUCCESS) {
			report("Failed to load blame data");
			return true;
		}

		if (view->env->goto_lineno > 0) {
			select_view_line(view, view->env->goto_lineno);
			view->env->goto_lineno = 0;
		}

		state->done_reading = true;
		return false;

	} else {
		struct blame *blame;

		if (!add_line_alloc(view, &blame, LINE_DEFAULT, buf->size, false))
			return false;

		blame->commit = NULL;
		strncpy(blame->text, buf->data, buf->size);
		blame->text[buf->size] = 0;
		return true;
	}
}