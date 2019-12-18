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

/* Variables and functions */
 scalar_t__ Columns ; 
 scalar_t__ Rows ; 
 scalar_t__* T_CWS ; 
 int /*<<< orphan*/  out_flush () ; 
 int /*<<< orphan*/  screen_start () ; 
 int /*<<< orphan*/  term_set_winsize (int,int) ; 

void
mch_set_shellsize()
{
    if (*T_CWS)
    {
	/*
	 * NOTE: if you get an error here that term_set_winsize() is
	 * undefined, check the output of configure.  It could probably not
	 * find a ncurses, termcap or termlib library.
	 */
	term_set_winsize((int)Rows, (int)Columns);
	out_flush();
	screen_start();			/* don't know where cursor is now */
    }
}