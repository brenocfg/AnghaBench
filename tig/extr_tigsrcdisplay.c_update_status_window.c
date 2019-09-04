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
typedef  int /*<<< orphan*/  va_list ;
struct view {scalar_t__ has_scrolled; } ;

/* Variables and functions */
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ input_mode ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int status_empty ; 
 int /*<<< orphan*/  status_win ; 
 size_t strlen (char const*) ; 
 scalar_t__ use_scroll_status_wclear ; 
 int /*<<< orphan*/  vwprintw (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
update_status_window(struct view *view, const char *context, const char *msg, va_list args)
{
	if (input_mode)
		return false;

	if (!status_empty || *msg) {
		wmove(status_win, 0, 0);
		if (view && view->has_scrolled && use_scroll_status_wclear)
			wclear(status_win);
		if (*msg) {
			vwprintw(status_win, msg, args);
			status_empty = false;
		} else {
			status_empty = true;
		}
		wclrtoeol(status_win);

		if (context && *context) {
			size_t contextlen = strlen(context);
			int x, y, width, ___;

			getyx(status_win, y, x);
			getmaxyx(status_win, ___, width);
			(void) ___;
			if (contextlen < width - x) {
				mvwprintw(status_win, 0, width - contextlen, "%s", context);
				wmove(status_win, y, x);
			}
		}

		return true;
	}

	return false;
}