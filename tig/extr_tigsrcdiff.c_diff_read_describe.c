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
struct view {int /*<<< orphan*/  line; } ;
struct line {int dummy; } ;
struct diff_state {int dummy; } ;
struct buffer {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_PP_REFS ; 
 int /*<<< orphan*/  append_line_format (struct view*,struct line*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  box_text (struct line*) ; 
 struct line* find_next_line_by_type (struct view*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char* string_trim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
diff_read_describe(struct view *view, struct buffer *buffer, struct diff_state *state)
{
	struct line *line = find_next_line_by_type(view, view->line, LINE_PP_REFS);

	if (line && buffer) {
		const char *ref = string_trim(buffer->data);
		const char *sep = !strcmp("Refs: ", box_text(line)) ? "" : ", ";

		if (*ref && !append_line_format(view, line, "%s%s", sep, ref))
			return false;
	}

	return true;
}