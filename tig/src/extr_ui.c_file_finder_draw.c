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
struct position {size_t lineno; size_t offset; } ;
struct file_finder_line {scalar_t__ matches; } ;
struct file_finder {int height; scalar_t__ searchlen; int /*<<< orphan*/  win; int /*<<< orphan*/  lines; struct file_finder_line** line; struct position pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_CURSOR ; 
 int /*<<< orphan*/  LINE_DEFAULT ; 
 int /*<<< orphan*/  LINE_TITLE_FOCUS ; 
 int /*<<< orphan*/  file_finder_draw_line (struct file_finder*,struct file_finder_line*) ; 
 int /*<<< orphan*/  get_line_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbkgdset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
file_finder_draw(struct file_finder *finder)
{
	struct position *pos = &finder->pos;
	struct file_finder_line *current_line = finder->line[pos->lineno];
	struct file_finder_line **line_pos = &finder->line[pos->offset];
	int column;

	wbkgdset(finder->win, get_line_attr(NULL, LINE_DEFAULT));
	werase(finder->win);

	for (column = 0; *line_pos && column < finder->height - 1; line_pos++) {
		struct file_finder_line *line = *line_pos;

		if (finder->searchlen != line->matches)
			continue;

		wmove(finder->win, column++, 0);
		if (line == current_line) {
			wbkgdset(finder->win, get_line_attr(NULL, LINE_CURSOR));
		}
		file_finder_draw_line(finder, line);
		if (line == current_line) {
			wclrtoeol(finder->win);
			wbkgdset(finder->win, get_line_attr(NULL, LINE_DEFAULT));
		}
	}

	wmove(finder->win, finder->height - 1, 0);
	wbkgdset(finder->win, get_line_attr(NULL, LINE_TITLE_FOCUS));
	wprintw(finder->win, "[finder] file %d of %d", pos->lineno + 1, finder->lines);
	wclrtoeol(finder->win);
	wrefresh(finder->win);
}