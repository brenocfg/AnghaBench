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
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int open (char*,int,int) ; 
 int tty_log_fd ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,long) ; 

void
tty_create_log(void)
{
	char	name[64];

	xsnprintf(name, sizeof name, "tmux-out-%ld.log", (long)getpid());

	tty_log_fd = open(name, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if (tty_log_fd != -1 && fcntl(tty_log_fd, F_SETFD, FD_CLOEXEC) == -1)
		fatal("fcntl failed");
}