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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kill_and_sigcont (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_terminate (int,int /*<<< orphan*/ *) ; 

void sigterm_wait(pid_t pid) {
        assert(pid > 1);

        if (kill_and_sigcont(pid, SIGTERM) >= 0)
                (void) wait_for_terminate(pid, NULL);
}