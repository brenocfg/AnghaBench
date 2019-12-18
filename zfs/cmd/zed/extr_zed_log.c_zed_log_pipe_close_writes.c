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
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_die (char*,int,...) ; 

void
zed_log_pipe_close_writes(void)
{
	if (_ctx.pipe_fd[1] < 0)
		zed_log_die(
		    "Invalid use of zed_log_pipe_close_writes in PID %d",
		    (int)getpid());

	if (close(_ctx.pipe_fd[1]) < 0)
		zed_log_die(
		    "Failed to close writes on daemonize pipe in PID %d: %s",
		    (int)getpid(), strerror(errno));

	_ctx.pipe_fd[1] = -1;
}