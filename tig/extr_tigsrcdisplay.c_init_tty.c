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
struct termios {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  opgrp; int /*<<< orphan*/  attr; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  die_callback ; 
 int /*<<< orphan*/  done_display ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 TYPE_1__ opt_tty ; 
 int /*<<< orphan*/  setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetpgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcsetpgrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
init_tty(void)
{
	/* open */
	opt_tty.file = fopen("/dev/tty", "r+");
	if (!opt_tty.file)
		die("Failed to open tty for input");
	opt_tty.fd = fileno(opt_tty.file);

	/* attributes */
	opt_tty.attr = calloc(1, sizeof(struct termios));
	if (!opt_tty.attr)
		die("Failed allocation for tty attributes");
	tcgetattr(opt_tty.fd, opt_tty.attr);

	/* process-group leader */
	signal(SIGTTOU, SIG_IGN);
	setpgid(getpid(), getpid());
	opt_tty.opgrp = tcgetpgrp(opt_tty.fd);
	tcsetpgrp(opt_tty.fd, getpid());
	signal(SIGTTOU, SIG_DFL);

	die_callback = done_display;
}