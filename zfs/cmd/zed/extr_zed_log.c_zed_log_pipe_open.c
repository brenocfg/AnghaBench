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
struct TYPE_2__ {int* pipe_fd; } ;

/* Variables and functions */
 TYPE_1__ _ctx ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpid () ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_die (char*,int,...) ; 

void
zed_log_pipe_open(void)
{
	if ((_ctx.pipe_fd[0] != -1) || (_ctx.pipe_fd[1] != -1))
		zed_log_die("Invalid use of zed_log_pipe_open in PID %d",
		    (int)getpid());

	if (pipe(_ctx.pipe_fd) < 0)
		zed_log_die("Failed to create daemonize pipe in PID %d: %s",
		    (int)getpid(), strerror(errno));
}