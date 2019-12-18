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
struct view {int lines; TYPE_1__* line; struct main_state* private; } ;
struct commit {int /*<<< orphan*/ * title; int /*<<< orphan*/  graph; int /*<<< orphan*/  time; int /*<<< orphan*/  author; int /*<<< orphan*/ * id; } ;
struct main_state {int in_header; char* reflogmsg; scalar_t__ with_graph; struct commit current; scalar_t__ first_parent; struct graph* graph; } ;
struct graph {int /*<<< orphan*/  (* render_parents ) (struct graph*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* add_parent ) (struct graph*,char*) ;int /*<<< orphan*/  (* done_rendering ) (struct graph*) ;} ;
struct buffer {char* data; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;
struct TYPE_2__ {int dirty; struct commit* data; } ;

/* Variables and functions */
#define  LINE_AUTHOR 131 
 int LINE_COMMIT ; 
 int /*<<< orphan*/  LINE_MAIN_ANNOTATED ; 
 int /*<<< orphan*/  LINE_MAIN_COMMIT ; 
#define  LINE_PARENT 130 
#define  LINE_PP_REFLOG 129 
#define  LINE_PP_REFLOGMSG 128 
 int STRING_SIZE (char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ failed_to_load_initial_view (struct view*) ; 
 int /*<<< orphan*/  free (struct commit*) ; 
 int get_line_type (char*) ; 
 char* io_memchr (struct buffer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isalnum (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  main_add_commit (struct view*,int /*<<< orphan*/ ,struct commit*,char*,int) ; 
 int /*<<< orphan*/  main_add_reflog (struct view*,struct main_state*,char*) ; 
 int /*<<< orphan*/  main_flush_commit (struct view*,struct commit*) ; 
 int /*<<< orphan*/  main_register_commit (struct view*,struct commit*,char*,int) ; 
 int /*<<< orphan*/  parse_author_line (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  string_ncopy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct graph*) ; 
 int /*<<< orphan*/  stub2 (struct graph*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct graph*,char*) ; 
 int /*<<< orphan*/  stub4 (struct graph*,int /*<<< orphan*/ *) ; 

bool
main_read(struct view *view, struct buffer *buf, bool force_stop)
{
	struct main_state *state = view->private;
	struct graph *graph = state->graph;
	enum line_type type;
	struct commit *commit = &state->current;
	char *line;

	if (!buf) {
		main_flush_commit(view, commit);

		if (!force_stop && failed_to_load_initial_view(view))
			die("No revisions match the given arguments.");
		if (view->lines > 0) {
			struct commit *last = view->line[view->lines - 1].data;

			view->line[view->lines - 1].dirty = 1;
			if (!last->author) {
				view->lines--;
				free(last);
			}
		}

		if (state->graph)
			state->graph->done_rendering(graph);
		return true;
	}

	line = buf->data;
	type = get_line_type(line);
	if (type == LINE_COMMIT) {
		bool is_boundary;
		char *author;

		state->in_header = true;
		line += STRING_SIZE("commit ");
		is_boundary = *line == '-';
		while (*line && !isalnum(*line))
			line++;

		main_flush_commit(view, commit);

		author = io_memchr(buf, line, 0);

		if (state->first_parent) {
			char *parent = strchr(line, ' ');
			char *parent_end = parent ? strchr(parent + 1, ' ') : NULL;

			if (parent_end)
				*parent_end = 0;
		}

		main_register_commit(view, &state->current, line, is_boundary);

		if (author) {
			char *title = io_memchr(buf, author, 0);

			parse_author_line(author, &commit->author, &commit->time);
			if (state->with_graph)
				graph->render_parents(graph, &commit->graph);
			if (title) {
				char *notes = io_memchr(buf, title, 0);

				main_add_commit(view, notes && *notes ? LINE_MAIN_ANNOTATED : LINE_MAIN_COMMIT,
						commit, title, false);
			}
		}

		return true;
	}

	if (!*commit->id)
		return true;

	/* Empty line separates the commit header from the log itself. */
	if (*line == '\0')
		state->in_header = false;

	switch (type) {
	case LINE_PP_REFLOG:
		if (!main_add_reflog(view, state, line + STRING_SIZE("Reflog: ")))
			return false;
		break;

	case LINE_PP_REFLOGMSG:
		line += STRING_SIZE("Reflog message: ");
		string_ncopy(state->reflogmsg, line, strlen(line));
		break;

	case LINE_PARENT:
		if (state->with_graph)
			graph->add_parent(graph, line + STRING_SIZE("parent "));
		break;

	case LINE_AUTHOR:
		parse_author_line(line + STRING_SIZE("author "),
				  &commit->author, &commit->time);
		if (state->with_graph)
			graph->render_parents(graph, &commit->graph);
		break;

	default:
		/* Fill in the commit title if it has not already been set. */
		if (*commit->title)
			break;

		/* Skip lines in the commit header. */
		if (state->in_header)
			break;

		/* Require titles to start with a non-space character at the
		 * offset used by git log. */
		if (strncmp(line, "    ", 4))
			break;
		line += 4;
		/* Well, if the title starts with a whitespace character,
		 * try to be forgiving.  Otherwise we end up with no title. */
		while (isspace(*line))
			line++;
		if (*line == '\0')
			break;
		if (*state->reflogmsg)
			line = state->reflogmsg;
		main_add_commit(view, LINE_MAIN_COMMIT, commit, line, false);
	}

	return true;
}