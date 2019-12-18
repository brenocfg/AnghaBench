#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cgroup_path; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int cg_unified_controller (int /*<<< orphan*/ ) ; 
 int unit_watch_pids_in_path (TYPE_1__*,int /*<<< orphan*/ ) ; 

int unit_watch_all_pids(Unit *u) {
        int r;

        assert(u);

        /* Adds all PIDs from our cgroup to the set of PIDs we
         * watch. This is a fallback logic for cases where we do not
         * get reliable cgroup empty notifications: we try to use
         * SIGCHLD as replacement. */

        if (!u->cgroup_path)
                return -ENOENT;

        r = cg_unified_controller(SYSTEMD_CGROUP_CONTROLLER);
        if (r < 0)
                return r;
        if (r > 0) /* On unified we can use proper notifications */
                return 0;

        return unit_watch_pids_in_path(u, u->cgroup_path);
}