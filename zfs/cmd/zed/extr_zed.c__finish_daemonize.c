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
 int /*<<< orphan*/  O_RDWR ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 scalar_t__ close (int) ; 
 scalar_t__ dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_pipe_close_writes () ; 

__attribute__((used)) static void
_finish_daemonize(void)
{
	int devnull;

	/* Preserve fd 0/1/2, but discard data to/from stdin/stdout/stderr. */
	devnull = open("/dev/null", O_RDWR);
	if (devnull < 0)
		zed_log_die("Failed to open /dev/null: %s", strerror(errno));

	if (dup2(devnull, STDIN_FILENO) < 0)
		zed_log_die("Failed to dup /dev/null onto stdin: %s",
		    strerror(errno));

	if (dup2(devnull, STDOUT_FILENO) < 0)
		zed_log_die("Failed to dup /dev/null onto stdout: %s",
		    strerror(errno));

	if (dup2(devnull, STDERR_FILENO) < 0)
		zed_log_die("Failed to dup /dev/null onto stderr: %s",
		    strerror(errno));

	if ((devnull > STDERR_FILENO) && (close(devnull) < 0))
		zed_log_die("Failed to close /dev/null: %s", strerror(errno));

	/* Notify parent that daemonization is complete. */
	zed_log_pipe_close_writes();
}