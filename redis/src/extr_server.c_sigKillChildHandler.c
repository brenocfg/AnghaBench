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
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SERVER_CHILD_NOERROR_RETVAL ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  exitFromChild (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLogFromHandler (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void sigKillChildHandler(int sig) {
    UNUSED(sig);
    serverLogFromHandler(LL_WARNING, "Received SIGUSR1 in child, exiting now.");
    exitFromChild(SERVER_CHILD_NOERROR_RETVAL);
}