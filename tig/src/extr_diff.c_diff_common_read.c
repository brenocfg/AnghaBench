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
struct view {int /*<<< orphan*/  lines; } ;
struct line {int commit_title; struct box* data; } ;
struct diff_state {int combined_diff; int reading_diff_chunk; int reading_diff_stat; int after_diff; int after_commit_title; scalar_t__ highlight; } ;
struct box {int /*<<< orphan*/  cells; TYPE_1__* cell; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;
struct TYPE_2__ {int length; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int LINE_COMMIT ; 
 int LINE_DEFAULT ; 
 int LINE_DIFF_ADD ; 
 int LINE_DIFF_ADD2 ; 
 int LINE_DIFF_ADD_FILE ; 
 int LINE_DIFF_CHUNK ; 
 int LINE_DIFF_DEL ; 
 int LINE_DIFF_DEL2 ; 
 int LINE_DIFF_DEL_FILE ; 
 int LINE_DIFF_HEADER ; 
 int LINE_DIFF_START ; 
 int /*<<< orphan*/  LINE_DIFF_STAT ; 
 struct line* add_line_text (struct view*,char const*,int) ; 
 struct line* add_line_text_at (struct view*,int /*<<< orphan*/ ,char const*,int,int const) ; 
 int chunk_header_marker_length (char const*) ; 
 scalar_t__ diff_common_add_diff_stat (struct view*,char const*,int /*<<< orphan*/ ) ; 
 int diff_common_highlight (struct view*,char const*,int) ; 
 int get_line_type (char const*) ; 
 int pager_common_read (struct view*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 scalar_t__ strchr (char const*,int) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

bool
diff_common_read(struct view *view, const char *data, struct diff_state *state)
{
	enum line_type type = get_line_type(data);

	/* ADD2 and DEL2 are only valid in combined diff hunks */
	if (!state->combined_diff && (type == LINE_DIFF_ADD2 || type == LINE_DIFF_DEL2))
		type = LINE_DEFAULT;

	/* DEL_FILE, ADD_FILE and START are only valid outside diff chunks */
	if (state->reading_diff_chunk) {
		if (type == LINE_DIFF_DEL_FILE || type == LINE_DIFF_START)
			type = LINE_DIFF_DEL;
		else if (type == LINE_DIFF_ADD_FILE)
			type = LINE_DIFF_ADD;
	}

	if (!view->lines && type != LINE_COMMIT)
		state->reading_diff_stat = true;

	/* combined diffs lack LINE_DIFF_START and we don't know
	 * if this is a combined diff until we see a "@@@" */
	if (!state->after_diff && data[0] == ' ' && data[1] != ' ')
		state->reading_diff_stat = true;

	if (state->reading_diff_stat) {
		if (diff_common_add_diff_stat(view, data, 0))
			return true;
		state->reading_diff_stat = false;

	} else if (type == LINE_DIFF_START) {
		state->reading_diff_stat = true;
	}

	if (!state->after_commit_title && !prefixcmp(data, "    ")) {
		struct line *line = add_line_text(view, data, LINE_DEFAULT);

		if (line)
			line->commit_title = 1;
		state->after_commit_title = true;
		return line != NULL;
	}

	if (type == LINE_DIFF_HEADER) {
		state->after_diff = true;
		state->reading_diff_chunk = false;

	} else if (type == LINE_DIFF_CHUNK) {
		const int len = chunk_header_marker_length(data);
		const char *context = strstr(data + len, "@@");
		struct line *line =
			context ? add_line_text_at(view, view->lines, data, LINE_DIFF_CHUNK, len)
				: NULL;
		struct box *box;

		if (!line)
			return false;

		box = line->data;
		box->cell[0].length = (context + len) - data;
		box->cell[1].length = strlen(context + len);
		box->cell[box->cells++].type = LINE_DIFF_STAT;
		state->combined_diff = (len > 2);
		state->reading_diff_chunk = true;
		return true;

	} else if (type == LINE_COMMIT) {
		state->reading_diff_chunk = false;

	} else if (state->highlight && strchr(data, 0x1b)) {
		return diff_common_highlight(view, data, type);

	}

	return pager_common_read(view, data, type, NULL);
}