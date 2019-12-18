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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int FORK_DEATHSIG ; 
 int FORK_LOG ; 
 int FORK_RESET_SIGNALS ; 
 int FORK_RLIMIT_NOFILE_SAFE ; 
 int /*<<< orphan*/  WAIT_LOG_ABNORMAL ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execv (char const* const,char**) ; 
 int /*<<< orphan*/  log_error_errno (int /*<<< orphan*/ ,char*,char const* const) ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 
 int wait_for_terminate_and_check (char const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fork_wait(const char* const cmdline[]) {
        pid_t pid;
        int r;

        r = safe_fork("(sulogin)", FORK_RESET_SIGNALS|FORK_DEATHSIG|FORK_RLIMIT_NOFILE_SAFE|FORK_LOG, &pid);
        if (r < 0)
                return r;
        if (r == 0) {
                /* Child */
                execv(cmdline[0], (char**) cmdline);
                log_error_errno(errno, "Failed to execute %s: %m", cmdline[0]);
                _exit(EXIT_FAILURE); /* Operational error */
        }

        return wait_for_terminate_and_check(cmdline[0], pid, WAIT_LOG_ABNORMAL);
}