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
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ agent_pid ; 
 int /*<<< orphan*/  kill_and_sigcont (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_terminate (scalar_t__,int /*<<< orphan*/ *) ; 

void ask_password_agent_close(void) {

        if (agent_pid <= 0)
                return;

        /* Inform agent that we are done */
        (void) kill_and_sigcont(agent_pid, SIGTERM);
        (void) wait_for_terminate(agent_pid, NULL);
        agent_pid = 0;
}