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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ fork () ; 
 int getpid_cached () ; 
 int pid_is_alive (int) ; 
 int /*<<< orphan*/  waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_pid_is_alive(void) {
        pid_t pid;

        pid = fork();
        assert_se(pid >= 0);
        if (pid == 0) {
                _exit(EXIT_SUCCESS);
        } else {
                int status;

                waitpid(pid, &status, 0);
                assert_se(!pid_is_alive(pid));
        }
        assert_se(pid_is_alive(getpid_cached()));
        assert_se(!pid_is_alive(-1));
}