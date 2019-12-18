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

/* Variables and functions */
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WTERMSIG (int) ; 
 int /*<<< orphan*/  test_fail (char*,...) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wait_for_child_exit(int pid) {
	int status;
	while (true) {
		if (waitpid(pid, &status, 0) == -1) {
			test_fail("Unexpected waitpid() failure.");
		}
		if (WIFSIGNALED(status)) {
			test_fail("Unexpected child termination due to "
			    "signal %d", WTERMSIG(status));
			break;
		}
		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) != 0) {
				test_fail("Unexpected child exit value %d",
				    WEXITSTATUS(status));
			}
			break;
		}
	}
}