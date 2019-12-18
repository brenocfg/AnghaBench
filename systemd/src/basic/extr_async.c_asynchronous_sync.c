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
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int FORK_CLOSE_ALL_FDS ; 
 int FORK_RESET_SIGNALS ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync () ; 

int asynchronous_sync(pid_t *ret_pid) {
        int r;

        /* This forks off an invocation of fork() as a child process, in order to initiate synchronization to
         * disk. Note that we implement this as helper process rather than thread as we don't want the sync() to hang our
         * original process ever, and a thread would do that as the process can't exit with threads hanging in blocking
         * syscalls. */

        r = safe_fork("(sd-sync)", FORK_RESET_SIGNALS|FORK_CLOSE_ALL_FDS, ret_pid);
        if (r < 0)
                return r;
        if (r == 0) {
                /* Child process */
                (void) sync();
                _exit(EXIT_SUCCESS);
        }

        return 0;
}