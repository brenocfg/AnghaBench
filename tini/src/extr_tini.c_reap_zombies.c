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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 int /*<<< orphan*/  INT32_BITFIELD_CHECK_BOUNDS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INT32_BITFIELD_TEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRINT_DEBUG (char*,int) ; 
 int /*<<< orphan*/  PRINT_FATAL (char*,...) ; 
 int /*<<< orphan*/  PRINT_INFO (char*,int) ; 
 int /*<<< orphan*/  PRINT_TRACE (char*) ; 
 int /*<<< orphan*/  PRINT_WARNING (char*,int) ; 
 scalar_t__ STATUS_MAX ; 
 scalar_t__ STATUS_MIN ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  expect_status ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strsignal (int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_on_reap ; 

int reap_zombies(const pid_t child_pid, int* const child_exitcode_ptr) {
	pid_t current_pid;
	int current_status;

	while (1) {
		current_pid = waitpid(-1, &current_status, WNOHANG);

		switch (current_pid) {

			case -1:
				if (errno == ECHILD) {
					PRINT_TRACE("No child to wait");
					break;
				}
				PRINT_FATAL("Error while waiting for pids: '%s'", strerror(errno));
				return 1;

			case 0:
				PRINT_TRACE("No child to reap");
				break;

			default:
				/* A child was reaped. Check whether it's the main one. If it is, then
				 * set the exit_code, which will cause us to exit once we've reaped everyone else.
				 */
				PRINT_DEBUG("Reaped child with pid: '%i'", current_pid);
				if (current_pid == child_pid) {
					if (WIFEXITED(current_status)) {
						/* Our process exited normally. */
						PRINT_INFO("Main child exited normally (with status '%i')", WEXITSTATUS(current_status));
						*child_exitcode_ptr = WEXITSTATUS(current_status);
					} else if (WIFSIGNALED(current_status)) {
						/* Our process was terminated. Emulate what sh / bash
						 * would do, which is to return 128 + signal number.
						 */
						PRINT_INFO("Main child exited with signal (with signal '%s')", strsignal(WTERMSIG(current_status)));
						*child_exitcode_ptr = 128 + WTERMSIG(current_status);
					} else {
						PRINT_FATAL("Main child exited for unknown reason");
						return 1;
					}

					// Be safe, ensure the status code is indeed between 0 and 255.
					*child_exitcode_ptr = *child_exitcode_ptr % (STATUS_MAX - STATUS_MIN + 1);

					// If this exitcode was remapped, then set it to 0.
					INT32_BITFIELD_CHECK_BOUNDS(expect_status, *child_exitcode_ptr);
					if (INT32_BITFIELD_TEST(expect_status, *child_exitcode_ptr)) {
						*child_exitcode_ptr = 0;
					}
				} else if (warn_on_reap > 0) {
					PRINT_WARNING("Reaped zombie process with pid=%i", current_pid);
				}

				// Check if other childs have been reaped.
				continue;
		}

		/* If we make it here, that's because we did not continue in the switch case. */
		break;
	}

	return 0;
}