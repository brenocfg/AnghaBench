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
struct view {char* vid; TYPE_1__* env; } ;
struct line {scalar_t__ type; } ;
struct blame_header {char* id; int orig_lineno; } ;
struct blame_commit {char const* filename; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {char* ref; unsigned long goto_lineno; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 scalar_t__ LINE_DIFF_ADD ; 
 int /*<<< orphan*/  LINE_DIFF_CHUNK ; 
 scalar_t__ LINE_DIFF_DEL ; 
 int /*<<< orphan*/  LINE_DIFF_HEADER ; 
 int REQ_NONE ; 
 int REQ_VIEW_BLAME ; 
 int SIZEOF_REF ; 
 int STRING_SIZE (char*) ; 
 char* box_text (struct line*) ; 
 int /*<<< orphan*/  diff_blame_line (char*,char const*,unsigned long,struct blame_header*,struct blame_commit*) ; 
 struct line* find_prev_line_by_type (struct view*,struct line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_chunk_lineno (unsigned long*,char const*,int) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  string_copy (char*,char*) ; 
 int /*<<< orphan*/  string_format (char*,char*,char*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ string_rev_is_null (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static enum request
diff_trace_origin(struct view *view, struct line *line)
{
	struct line *diff = find_prev_line_by_type(view, line, LINE_DIFF_HEADER);
	struct line *chunk = find_prev_line_by_type(view, line, LINE_DIFF_CHUNK);
	const char *chunk_data;
	int chunk_marker = line->type == LINE_DIFF_DEL ? '-' : '+';
	unsigned long lineno = 0;
	const char *file = NULL;
	char ref[SIZEOF_REF];
	struct blame_header header;
	struct blame_commit commit;

	if (!diff || !chunk || chunk == line) {
		report("The line to trace must be inside a diff chunk");
		return REQ_NONE;
	}

	for (; diff < line && !file; diff++) {
		const char *data = box_text(diff);

		if (!prefixcmp(data, "--- a/")) {
			file = data + STRING_SIZE("--- a/");
			break;
		}
	}

	if (diff == line || !file) {
		report("Failed to read the file name");
		return REQ_NONE;
	}

	chunk_data = box_text(chunk);

	if (!parse_chunk_lineno(&lineno, chunk_data, chunk_marker)) {
		report("Failed to read the line number");
		return REQ_NONE;
	}

	if (lineno == 0) {
		report("This is the origin of the line");
		return REQ_NONE;
	}

	for (chunk += 1; chunk < line; chunk++) {
		if (chunk->type == LINE_DIFF_ADD) {
			lineno += chunk_marker == '+';
		} else if (chunk->type == LINE_DIFF_DEL) {
			lineno += chunk_marker == '-';
		} else {
			lineno++;
		}
	}

	if (chunk_marker == '+')
		string_copy(ref, view->vid);
	else
		string_format(ref, "%s^", view->vid);

	if (string_rev_is_null(ref)) {
		string_ncopy(view->env->file, file, strlen(file));
		string_copy(view->env->ref, "");
		view->env->goto_lineno = lineno - 1;

	} else {
		if (!diff_blame_line(ref, file, lineno, &header, &commit)) {
			report("Failed to read blame data");
			return REQ_NONE;
		}

		string_ncopy(view->env->file, commit.filename, strlen(commit.filename));
		string_copy(view->env->ref, header.id);
		view->env->goto_lineno = header.orig_lineno - 1;
	}

	return REQ_VIEW_BLAME;
}