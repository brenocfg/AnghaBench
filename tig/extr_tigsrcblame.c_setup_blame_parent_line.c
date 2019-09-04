#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int lineno; } ;
struct view {TYPE_3__ pos; TYPE_1__* env; } ;
struct io {int dummy; } ;
struct buffer {char* data; } ;
struct blame {int lineno; int /*<<< orphan*/  text; TYPE_2__* commit; } ;
struct TYPE_5__ {int /*<<< orphan*/  filename; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  file; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_RD ; 
 int SIZEOF_REF ; 
 int SIZEOF_STR ; 
 int atoi (char*) ; 
 char* encoding_arg ; 
 int /*<<< orphan*/  io_done (struct io*) ; 
 scalar_t__ io_get (struct io*,struct buffer*,char,int) ; 
 int /*<<< orphan*/  io_run (struct io*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_format (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setup_blame_parent_line(struct view *view, struct blame *blame)
{
	char from[SIZEOF_REF + SIZEOF_STR];
	char to[SIZEOF_REF + SIZEOF_STR];
	const char *diff_tree_argv[] = {
		"git", "diff", encoding_arg, "--no-textconv", "--no-ext-diff",
			"--no-color", "-U0", from, to, "--", NULL
	};
	struct io io;
	int parent_lineno = -1;
	int blamed_lineno = -1;
	struct buffer buf;

	if (!string_format(from, "%s:%s", view->env->ref, view->env->file) ||
	    !string_format(to, "%s:%s", blame->commit->id, blame->commit->filename) ||
	    !io_run(&io, IO_RD, NULL, NULL, diff_tree_argv))
		return;

	while (io_get(&io, &buf, '\n', true)) {
		char *line = buf.data;

		if (*line == '@') {
			char *pos = strchr(line, '+');

			parent_lineno = atoi(line + 4);
			if (pos)
				blamed_lineno = atoi(pos + 1);

		} else if (*line == '+' && parent_lineno != -1) {
			if (blame->lineno == blamed_lineno - 1 &&
			    !strcmp(blame->text, line + 1)) {
				view->pos.lineno = parent_lineno ? parent_lineno - 1 : 0;
				break;
			}
			blamed_lineno++;
		}
	}

	io_done(&io);
}