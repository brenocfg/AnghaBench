#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ si_code; int si_status; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SIGNALS (int /*<<< orphan*/ ) ; 
 scalar_t__ CLD_EXITED ; 
 int FORK_CLOSE_ALL_FDS ; 
 int FORK_DEATHSIG ; 
 int FORK_NULL_STDIO ; 
 int FORK_REOPEN_LOG ; 
 int FORK_RESET_SIGNALS ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ wait_for_terminate (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void test_safe_fork(void) {
        siginfo_t status;
        pid_t pid;
        int r;

        BLOCK_SIGNALS(SIGCHLD);

        r = safe_fork("(test-child)", FORK_RESET_SIGNALS|FORK_CLOSE_ALL_FDS|FORK_DEATHSIG|FORK_NULL_STDIO|FORK_REOPEN_LOG, &pid);
        assert_se(r >= 0);

        if (r == 0) {
                /* child */
                usleep(100 * USEC_PER_MSEC);

                _exit(88);
        }

        assert_se(wait_for_terminate(pid, &status) >= 0);
        assert_se(status.si_code == CLD_EXITED);
        assert_se(status.si_status == 88);
}