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
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execv (char const*,char**) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int /*<<< orphan*/  log_error_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ null_or_empty_path (char const*) ; 
 int rearrange_stdio (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlimit_nofile_safe () ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_spawn(const char *path, char *argv[], int stdout_fd, pid_t *pid) {

        pid_t _pid;
        int r;

        if (null_or_empty_path(path)) {
                log_debug("%s is empty (a mask).", path);
                return 0;
        }

        r = safe_fork("(direxec)", FORK_DEATHSIG|FORK_LOG, &_pid);
        if (r < 0)
                return r;
        if (r == 0) {
                char *_argv[2];

                if (stdout_fd >= 0) {
                        r = rearrange_stdio(STDIN_FILENO, stdout_fd, STDERR_FILENO);
                        if (r < 0)
                                _exit(EXIT_FAILURE);
                }

                (void) rlimit_nofile_safe();

                if (!argv) {
                        _argv[0] = (char*) path;
                        _argv[1] = NULL;
                        argv = _argv;
                } else
                        argv[0] = (char*) path;

                execv(path, argv);
                log_error_errno(errno, "Failed to execute %s: %m", path);
                _exit(EXIT_FAILURE);
        }

        *pid = _pid;
        return 1;
}