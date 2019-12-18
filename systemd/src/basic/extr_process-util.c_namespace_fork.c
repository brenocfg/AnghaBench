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
typedef  int ForkFlags ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 scalar_t__ FLAGS_SET (int,int /*<<< orphan*/ ) ; 
 int FORK_CLOSE_ALL_FDS ; 
 int FORK_DEATHSIG ; 
 int /*<<< orphan*/  FORK_LOG ; 
 int FORK_MOUNTNS_SLAVE ; 
 int FORK_NEW_MOUNTNS ; 
 int FORK_NULL_STDIO ; 
 int FORK_REOPEN_LOG ; 
 int FORK_RESET_SIGNALS ; 
 int FORK_WAIT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  WAIT_LOG ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  log_full_errno (int /*<<< orphan*/ ,int,char*) ; 
 int namespace_enter (int,int,int,int,int) ; 
 int safe_fork_full (char const*,int const*,size_t,int,int /*<<< orphan*/ *) ; 
 int wait_for_terminate_and_check (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int namespace_fork(
                const char *outer_name,
                const char *inner_name,
                const int except_fds[],
                size_t n_except_fds,
                ForkFlags flags,
                int pidns_fd,
                int mntns_fd,
                int netns_fd,
                int userns_fd,
                int root_fd,
                pid_t *ret_pid) {

        int r;

        /* This is much like safe_fork(), but forks twice, and joins the specified namespaces in the middle
         * process. This ensures that we are fully a member of the destination namespace, with pidns an all, so that
         * /proc/self/fd works correctly. */

        r = safe_fork_full(outer_name, except_fds, n_except_fds, (flags|FORK_DEATHSIG) & ~(FORK_REOPEN_LOG|FORK_NEW_MOUNTNS|FORK_MOUNTNS_SLAVE), ret_pid);
        if (r < 0)
                return r;
        if (r == 0) {
                pid_t pid;

                /* Child */

                r = namespace_enter(pidns_fd, mntns_fd, netns_fd, userns_fd, root_fd);
                if (r < 0) {
                        log_full_errno(FLAGS_SET(flags, FORK_LOG) ? LOG_ERR : LOG_DEBUG, r, "Failed to join namespace: %m");
                        _exit(EXIT_FAILURE);
                }

                /* We mask a few flags here that either make no sense for the grandchild, or that we don't have to do again */
                r = safe_fork_full(inner_name, except_fds, n_except_fds, flags & ~(FORK_WAIT|FORK_RESET_SIGNALS|FORK_CLOSE_ALL_FDS|FORK_NULL_STDIO), &pid);
                if (r < 0)
                        _exit(EXIT_FAILURE);
                if (r == 0) {
                        /* Child */
                        if (ret_pid)
                                *ret_pid = pid;
                        return 0;
                }

                r = wait_for_terminate_and_check(inner_name, pid, FLAGS_SET(flags, FORK_LOG) ? WAIT_LOG : 0);
                if (r < 0)
                        _exit(EXIT_FAILURE);

                _exit(r);
        }

        return 1;
}