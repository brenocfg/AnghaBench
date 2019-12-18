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
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fork_test(void (*test_func)(void)) {
        pid_t pid = 0;

        pid = fork();
        assert_se(pid >= 0);
        if (pid == 0) {
                test_func();
                exit(EXIT_SUCCESS);
        } else if (pid > 0) {
                int status;

                assert_se(waitpid(pid, &status, 0) > 0);
                assert_se(WIFEXITED(status) && WEXITSTATUS(status) == 0);
        }
}