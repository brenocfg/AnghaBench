#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct view {struct log_state* private; } ;
struct log_state {int graph_indent; int commit_title_read; int after_commit_header; int reading_diff_stat; } ;
struct line {int graph_indent; } ;
struct buffer {char* data; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int LINE_COMMIT ; 
 struct line* diff_common_add_diff_stat (struct view*,char*,int) ; 
 int get_graph_indent (char*) ; 
 int get_line_type (char*) ; 
 int /*<<< orphan*/  pager_common_read (struct view*,char*,int,struct line**) ; 
 size_t strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static bool
log_read(struct view *view, struct buffer *buf, bool force_stop)
{
	struct line *line = NULL;
	enum line_type type;
	struct log_state *state = view->private;
	size_t len;
	char *commit;
	char *data;

	if (!buf)
		return true;

	data = buf->data;
	commit = strstr(data, "commit ");
	if (commit && get_graph_indent(data) == commit - data)
		state->graph_indent = commit - data;

	type = get_line_type(data + state->graph_indent);
	len = strlen(data + state->graph_indent);

	if (type == LINE_COMMIT)
		state->commit_title_read = true;
	else if (state->commit_title_read && len < 1) {
		state->commit_title_read = false;
		state->after_commit_header = true;
	} else if (state->after_commit_header && len < 1) {
		state->after_commit_header = false;
		state->reading_diff_stat = true;
	} else if (state->reading_diff_stat) {
		line = diff_common_add_diff_stat(view, data, state->graph_indent);
		if (line) {
			if (state->graph_indent)
				line->graph_indent = 1;
			return true;
		}
		state->reading_diff_stat = false;
	}

	if (!pager_common_read(view, data, type, &line))
		return false;
	if (line && state->graph_indent)
		line->graph_indent = 1;
	return true;
}