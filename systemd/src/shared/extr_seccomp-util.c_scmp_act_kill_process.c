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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCMP_ACT_KILL ; 
 int /*<<< orphan*/  SCMP_ACT_KILL_PROCESS ; 
 int seccomp_api_get () ; 

uint32_t scmp_act_kill_process(void) {

        /* Returns SCMP_ACT_KILL_PROCESS if it's supported, and SCMP_ACT_KILL_THREAD otherwise. We never
         * actually want to use SCMP_ACT_KILL_THREAD as its semantics are nuts (killing arbitrary threads of
         * a program is just a bad idea), but on old kernels/old libseccomp it is all we have, and at least
         * for single-threaded apps does the right thing. */

#ifdef SCMP_ACT_KILL_PROCESS
        if (seccomp_api_get() >= 3)
                return SCMP_ACT_KILL_PROCESS;
#endif

        return SCMP_ACT_KILL; /* same as SCMP_ACT_KILL_THREAD */
}