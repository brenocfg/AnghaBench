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
typedef  int /*<<< orphan*/  Unit ;
typedef  char const Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int /*<<< orphan*/ * manager_get_unit_by_cgroup (char const*,char const*) ; 
 int /*<<< orphan*/  unit_add_to_cgroup_empty_queue (int /*<<< orphan*/ *) ; 

int manager_notify_cgroup_empty(Manager *m, const char *cgroup) {
        Unit *u;

        assert(m);
        assert(cgroup);

        /* Called on the legacy hierarchy whenever we get an explicit cgroup notification from the cgroup agent process
         * or from the --system instance */

        log_debug("Got cgroup empty notification for: %s", cgroup);

        u = manager_get_unit_by_cgroup(m, cgroup);
        if (!u)
                return 0;

        unit_add_to_cgroup_empty_queue(u);
        return 1;
}