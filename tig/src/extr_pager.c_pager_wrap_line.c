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
struct view {int lines; struct line* line; scalar_t__ width; } ;
struct line {size_t lineno; int wrapped; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 struct line* add_line_text_at_ (struct view*,int,char const*,size_t,int,int,int) ; 
 int /*<<< orphan*/  opt_tab_size ; 
 size_t string_expanded_length (char const*,size_t,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static struct line *
pager_wrap_line(struct view *view, const char *data, enum line_type type)
{
	size_t first_line = 0;
	bool has_first_line = false;
	size_t datalen = strlen(data);
	size_t lineno = 0;

	while (datalen > 0 || !has_first_line) {
		bool wrapped = !!first_line;
		size_t linelen = string_expanded_length(data, datalen, opt_tab_size, view->width - !!wrapped);
		struct line *line;

		line = add_line_text_at_(view, view->lines, data, linelen, type, 1, wrapped);
		if (!line)
			break;
		if (!has_first_line) {
			first_line = view->lines - 1;
			has_first_line = true;
		}

		if (!wrapped)
			lineno = line->lineno;

		line->wrapped = wrapped;
		line->lineno = lineno;

		datalen -= linelen;
		data += linelen;
	}

	return has_first_line ? &view->line[first_line] : NULL;
}