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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 int /*<<< orphan*/  WAIT_ANY ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int WNOHANG ; 
 int WUNTRACED ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  server_child_exited (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_child_stopped (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
server_child_signal(void)
{
	int	 status;
	pid_t	 pid;

	for (;;) {
		switch (pid = waitpid(WAIT_ANY, &status, WNOHANG|WUNTRACED)) {
		case -1:
			if (errno == ECHILD)
				return;
			fatal("waitpid failed");
		case 0:
			return;
		}
		if (WIFSTOPPED(status))
			server_child_stopped(pid, status);
		else if (WIFEXITED(status) || WIFSIGNALED(status))
			server_child_exited(pid, status);
	}
}