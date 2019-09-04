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
struct TYPE_2__ {int /*<<< orphan*/  opgrp; int /*<<< orphan*/  fd; int /*<<< orphan*/ * attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  curs_set (int) ; 
 int cursed ; 
 int /*<<< orphan*/  doupdate () ; 
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__ opt_tty ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ status_win ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  werase (scalar_t__) ; 

__attribute__((used)) static void
done_display(void)
{
	if (cursed) {
		if (status_win) {
			werase(status_win);
			doupdate();
		}
		curs_set(1);
		endwin();
	}
	cursed = false;

	if (opt_tty.attr) {
		tcsetattr(opt_tty.fd, TCSAFLUSH, opt_tty.attr);
		free(opt_tty.attr);
		opt_tty.attr = NULL;
	}
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(opt_tty.fd, opt_tty.opgrp);
	signal(SIGTTOU, SIG_DFL);
}