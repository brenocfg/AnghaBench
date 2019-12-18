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
struct view {size_t lines; int /*<<< orphan*/  pipe; struct line* line; TYPE_2__* env; int /*<<< orphan*/ * ref; TYPE_1__* ops; } ;
struct tree_state {int read_date; int /*<<< orphan*/  author_time; scalar_t__ author; int /*<<< orphan*/  commit; } ;
struct tree_entry {int /*<<< orphan*/  time; scalar_t__ author; int /*<<< orphan*/  commit; int /*<<< orphan*/  name; } ;
struct line {int dirty; struct tree_entry* data; } ;
struct buffer {char* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  exec_dir; } ;
struct TYPE_5__ {char* directory; } ;
struct TYPE_4__ {char* id; } ;

/* Variables and functions */
 scalar_t__ LINE_AUTHOR ; 
 scalar_t__ LINE_COMMIT ; 
 int /*<<< orphan*/  LINE_DIRECTORY ; 
 int /*<<< orphan*/  LINE_HEADER ; 
 int /*<<< orphan*/  OPEN_EXTRA ; 
 int STRING_SIZE (char*) ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ begin_update (struct view*,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 char* encoding_arg ; 
 scalar_t__ get_line_type (char*) ; 
 int /*<<< orphan*/  io_kill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_author_line (char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_3__ repo ; 
 int /*<<< orphan*/  report (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_copy_rev_from_commit_line (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  tree_entry (struct view*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  view_column_info_update (struct view*,struct line*) ; 

__attribute__((used)) static bool
tree_read_date(struct view *view, struct buffer *buf, struct tree_state *state)
{
	char *text = buf ? buf->data : NULL;

	if (!text && state->read_date) {
		state->read_date = false;
		return true;

	} else if (!text) {
		/* Find next entry to process */
		const char *log_file[] = {
			"git", "log", encoding_arg, "--no-color", "--pretty=raw",
				"--cc", "--raw", view->ops->id, "--", "%(directory)", NULL
		};

		if (!view->lines) {
			tree_entry(view, LINE_HEADER, view->env->directory, NULL, NULL, 0);
			tree_entry(view, LINE_DIRECTORY, "..", "040000", view->ref, 0);
			report("Tree is empty");
			return true;
		}

		if (begin_update(view, repo.exec_dir, log_file, OPEN_EXTRA) != SUCCESS) {
			report("Failed to load tree data");
			return true;
		}

		state->read_date = true;
		return false;

	} else if (*text == 'c' && get_line_type(text) == LINE_COMMIT) {
		string_copy_rev_from_commit_line(state->commit, text);

	} else if (*text == 'a' && get_line_type(text) == LINE_AUTHOR) {
		parse_author_line(text + STRING_SIZE("author "),
				  &state->author, &state->author_time);

	} else if (*text == ':') {
		char *pos;
		size_t annotated = 1;
		size_t i;

		pos = strrchr(text, '\t');
		if (!pos)
			return true;
		text = pos + 1;
		if (*view->env->directory && !strncmp(text, view->env->directory, strlen(view->env->directory)))
			text += strlen(view->env->directory);
		pos = strchr(text, '/');
		if (pos)
			*pos = 0;

		for (i = 1; i < view->lines; i++) {
			struct line *line = &view->line[i];
			struct tree_entry *entry = line->data;

			annotated += !!entry->author;
			if (entry->author || strcmp(entry->name, text))
				continue;

			string_copy_rev(entry->commit, state->commit);
			entry->author = state->author;
			entry->time = state->author_time;
			line->dirty = 1;
			view_column_info_update(view, line);
			break;
		}

		if (annotated == view->lines)
			io_kill(view->pipe);
	}
	return true;
}