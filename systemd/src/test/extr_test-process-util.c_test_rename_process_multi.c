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
struct TYPE_3__ {scalar_t__ si_code; scalar_t__ si_status; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ CLD_EXITED ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ EXIT_SUCCESS ; 
 int /*<<< orphan*/  _exit (scalar_t__) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  setresuid (int,int,int) ; 
 int /*<<< orphan*/  test_rename_process_now (char*,int) ; 
 int /*<<< orphan*/  test_rename_process_one (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_terminate (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static void test_rename_process_multi(void) {
        pid_t pid;

        pid = fork();
        assert_se(pid >= 0);

        if (pid > 0) {
                siginfo_t si;

                assert_se(wait_for_terminate(pid, &si) >= 0);
                assert_se(si.si_code == CLD_EXITED);
                assert_se(si.si_status == EXIT_SUCCESS);

                return;
        }

        /* child */
        test_rename_process_now("one", 1);
        test_rename_process_now("more", 0); /* longer than "one", hence truncated */
        (void) setresuid(99, 99, 99); /* change uid when running privileged */
        test_rename_process_now("time!", 0);
        test_rename_process_now("0", 1); /* shorter than "one", should fit */
        test_rename_process_one("", -EINVAL);
        test_rename_process_one(NULL, -EINVAL);
        _exit(EXIT_SUCCESS);
}