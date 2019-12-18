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
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int fd_nonblock (int,int) ; 
 int log_error_errno (int,char*,...) ; 
 int /*<<< orphan*/  log_warning_errno (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pipe (int*) ; 
 int rearrange_stdio (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlimit_nofile_safe () ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int /*<<< orphan*/  safe_close_pair (int*) ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spawn_child(const char* child, char** argv) {
        pid_t child_pid;
        int fd[2], r;

        if (pipe(fd) < 0)
                return log_error_errno(errno, "Failed to create pager pipe: %m");

        r = safe_fork("(remote)", FORK_RESET_SIGNALS|FORK_DEATHSIG|FORK_LOG, &child_pid);
        if (r < 0) {
                safe_close_pair(fd);
                return r;
        }

        /* In the child */
        if (r == 0) {
                safe_close(fd[0]);

                r = rearrange_stdio(STDIN_FILENO, fd[1], STDERR_FILENO);
                if (r < 0) {
                        log_error_errno(r, "Failed to dup pipe to stdout: %m");
                        _exit(EXIT_FAILURE);
                }

                (void) rlimit_nofile_safe();

                execvp(child, argv);
                log_error_errno(errno, "Failed to exec child %s: %m", child);
                _exit(EXIT_FAILURE);
        }

        safe_close(fd[1]);

        r = fd_nonblock(fd[0], true);
        if (r < 0)
                log_warning_errno(errno, "Failed to set child pipe to non-blocking: %m");

        return fd[0];
}