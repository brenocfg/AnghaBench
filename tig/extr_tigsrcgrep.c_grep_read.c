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
struct view {scalar_t__* ref; int /*<<< orphan*/  lines; struct grep_state* private; } ;
struct line {int dummy; } ;
struct grep_state {char const* last_file; int /*<<< orphan*/  no_file_group; } ;
struct grep_line {char const* file; int /*<<< orphan*/  text; int /*<<< orphan*/  lineno; } ;
struct buffer {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DEFAULT ; 
 int /*<<< orphan*/  LINE_DELIMITER ; 
 int /*<<< orphan*/  LINE_FILE ; 
 struct line* add_line_alloc (struct view*,struct grep_line**,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/ * add_line_nodata (struct view*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_line_text (struct view*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 char* get_path (char*) ; 
 char* io_memchr (struct buffer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  view_column_info_update (struct view*,struct line*) ; 

__attribute__((used)) static bool
grep_read(struct view *view, struct buffer *buf, bool force_stop)
{
	struct grep_state *state = view->private;
	struct grep_line *grep;
	char *lineno, *text;
	struct line *line;
	const char *file;
	size_t textlen;

	if (!buf) {
		state->last_file = NULL;
		if (!view->lines) {
			view->ref[0] = 0;
			report("No matches found");
		}
		return true;
	}

	if (!strcmp(buf->data, "--"))
		return add_line_nodata(view, LINE_DELIMITER) != NULL;

	lineno = io_memchr(buf, buf->data, 0);
	text = io_memchr(buf, lineno, 0);

	/*
	 * No data indicates binary file matches, e.g.:
	 *	> git grep vertical- -- test
	 *	test/graph/20-tig-all-long-test:● │ Add "auto" vertical-split
	 *	Binary file test/graph/20-tig-all-long-test.in matches
	 */
	if (!lineno || !text)
		return true;

	textlen = strlen(text);

	file = get_path(buf->data);
	if (!file)
		return false;

	if (!state->no_file_group && file != state->last_file &&
	    !add_line_text(view, file, LINE_FILE))
		return false;

	line = add_line_alloc(view, &grep, LINE_DEFAULT, textlen, false);
	if (!line)
		return false;

	grep->file = file;
	grep->lineno = atoi(lineno);
	if (grep->lineno > 0)
		grep->lineno -= 1;
	strncpy(grep->text, text, textlen + 1);
	view_column_info_update(view, line);

	state->last_file = file;

	return true;
}