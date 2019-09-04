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
typedef  char chtype ;

/* Variables and functions */
 char ACS_VLINE ; 
 int /*<<< orphan*/  LINE_TITLE_BLUR ; 
 scalar_t__ display_sep ; 
 char get_line_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_line_graphics ; 
 int /*<<< orphan*/  wbkgd (scalar_t__,char) ; 
 int /*<<< orphan*/  wclear (scalar_t__) ; 
 int /*<<< orphan*/  wnoutrefresh (scalar_t__) ; 

__attribute__((used)) static void
redraw_display_separator(bool clear)
{
	if (display_sep) {
		chtype separator = opt_line_graphics ? ACS_VLINE : '|';

		if (clear)
			wclear(display_sep);
		wbkgd(display_sep, separator + get_line_attr(NULL, LINE_TITLE_BLUR));
		wnoutrefresh(display_sep);
	}
}