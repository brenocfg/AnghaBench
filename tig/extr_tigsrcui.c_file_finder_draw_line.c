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
struct file_finder_line {char* text; } ;
struct file_finder {char** search; int /*<<< orphan*/  win; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_STANDOUT ; 
 char* strstr (char const*,char const*) ; 
 int /*<<< orphan*/  waddnstr (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
file_finder_draw_line(struct file_finder *finder, struct file_finder_line *line)
{
	const char **search = finder->search;
	const char *text = line->text;
	const char *pos;

	for (; *text && search && *search && (pos = strstr(text, *search)); search++) {
		if (text < pos)
			waddnstr(finder->win, text, pos - text);
		wattron(finder->win, A_STANDOUT);
		waddnstr(finder->win, pos, 1);
		wattroff(finder->win, A_STANDOUT);
		text = pos + 1;
	}

	if (*text)
		waddstr(finder->win, text);
}