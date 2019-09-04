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
struct view {struct diff_state* private; } ;
struct line {scalar_t__ type; } ;
struct diff_state {int combined_diff; int reading_diff_chunk; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 scalar_t__ LINE_COMMIT ; 
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
 int LINE_PP_MERGE ; 
 int STRING_SIZE (char*) ; 
 int /*<<< orphan*/  VIEW_ADD_PAGER_REFS ; 
 struct line* add_line_text (struct view*,char const*,int) ; 
 int /*<<< orphan*/  add_pager_refs (struct view*,char const*) ; 
 scalar_t__ opt_wrap_lines ; 
 struct line* pager_wrap_line (struct view*,char const*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ view_has_flags (struct view*,int /*<<< orphan*/ ) ; 

bool
pager_common_read(struct view *view, const char *data, enum line_type type, struct line **line_ptr)
{
	struct diff_state *state = view->private;
	struct line *line;

	if (!data)
		return true;

	if (type == LINE_DIFF_HEADER) {
		const int len = STRING_SIZE("diff --");

		if (!strncmp(data + len, "combined ", strlen("combined ")) ||
		    !strncmp(data + len, "cc ", strlen("cc ")))
			state->combined_diff = true;
		state->reading_diff_chunk = false;

	} else if (type == LINE_DIFF_CHUNK) {
		state->reading_diff_chunk = true;

	} else if (type == LINE_PP_MERGE) {
		state->combined_diff = true;
	}

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

	if (opt_wrap_lines) {
		line = pager_wrap_line(view, data, type);
	} else {
		line = add_line_text(view, data, type);
	}

	if (!line)
		return false;

	if (line_ptr)
		*line_ptr = line;

	if (line->type == LINE_COMMIT && view_has_flags(view, VIEW_ADD_PAGER_REFS))
		add_pager_refs(view, data + STRING_SIZE("commit "));

	return true;
}