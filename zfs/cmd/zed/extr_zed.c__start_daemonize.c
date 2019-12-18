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
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fork () ; 
 scalar_t__ setsid () ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_die (char*,...) ; 
 int /*<<< orphan*/  zed_log_pipe_close_reads () ; 
 int /*<<< orphan*/  zed_log_pipe_close_writes () ; 
 int /*<<< orphan*/  zed_log_pipe_open () ; 
 int /*<<< orphan*/  zed_log_pipe_wait () ; 

__attribute__((used)) static void
_start_daemonize(void)
{
	pid_t pid;
	struct sigaction sa;

	/* Create pipe for communicating with child during daemonization. */
	zed_log_pipe_open();

	/* Background process and ensure child is not process group leader. */
	pid = fork();
	if (pid < 0) {
		zed_log_die("Failed to create child process: %s",
		    strerror(errno));
	} else if (pid > 0) {

		/* Close writes since parent will only read from pipe. */
		zed_log_pipe_close_writes();

		/* Wait for notification that daemonization is complete. */
		zed_log_pipe_wait();

		zed_log_pipe_close_reads();
		_exit(EXIT_SUCCESS);
	}

	/* Close reads since child will only write to pipe. */
	zed_log_pipe_close_reads();

	/* Create independent session and detach from terminal. */
	if (setsid() < 0)
		zed_log_die("Failed to create new session: %s",
		    strerror(errno));

	/* Prevent child from terminating on HUP when session leader exits. */
	if (sigemptyset(&sa.sa_mask) < 0)
		zed_log_die("Failed to initialize sigset");

	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;

	if (sigaction(SIGHUP, &sa, NULL) < 0)
		zed_log_die("Failed to ignore SIGHUP");

	/* Ensure process cannot re-acquire terminal. */
	pid = fork();
	if (pid < 0) {
		zed_log_die("Failed to create grandchild process: %s",
		    strerror(errno));
	} else if (pid > 0) {
		_exit(EXIT_SUCCESS);
	}
}