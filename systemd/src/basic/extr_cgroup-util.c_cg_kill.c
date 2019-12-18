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
typedef  int /*<<< orphan*/  cg_kill_log_func_t ;
typedef  int /*<<< orphan*/  Set ;
typedef  int /*<<< orphan*/  CGroupFlags ;

/* Variables and functions */
 int SIGKILL ; 
 int cg_kill_items (char const*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,char*) ; 
 int cg_unified_controller (char const*) ; 

int cg_kill(
                const char *controller,
                const char *path,
                int sig,
                CGroupFlags flags,
                Set *s,
                cg_kill_log_func_t log_kill,
                void *userdata) {
        int r;

        r = cg_kill_items(controller, path, sig, flags, s, log_kill, userdata, "cgroup.procs");
        if (r < 0 || sig != SIGKILL)
                return r;

        /* Only in case of killing with SIGKILL and when using cgroupsv2, kill remaining threads manually as
           a workaround for kernel bug. It was fixed in 5.2-rc5 (c03cd7738a83), backported to 4.19.66
           (4340d175b898) and 4.14.138 (feb6b123b7dd). */
        r = cg_unified_controller(controller);
        if (r <= 0)
                return r;

        return cg_kill_items(controller, path, sig, flags, s, log_kill, userdata, "cgroup.threads");
}