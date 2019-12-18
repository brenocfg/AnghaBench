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
struct TYPE_5__ {int /*<<< orphan*/  pids; int /*<<< orphan*/  cgroup_path; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int cg_unified_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_add_to_cgroup_empty_queue (TYPE_1__*) ; 

int unit_synthesize_cgroup_empty_event(Unit *u) {
        int r;

        assert(u);

        /* Enqueue a synthetic cgroup empty event if this unit doesn't watch any PIDs anymore. This is compatibility
         * support for non-unified systems where notifications aren't reliable, and hence need to take whatever we can
         * get as notification source as soon as we stopped having any useful PIDs to watch for. */

        if (!u->cgroup_path)
                return -ENOENT;

        r = cg_unified_controller(SYSTEMD_CGROUP_CONTROLLER);
        if (r < 0)
                return r;
        if (r > 0) /* On unified we have reliable notifications, and don't need this */
                return 0;

        if (!set_isempty(u->pids))
                return 0;

        unit_add_to_cgroup_empty_queue(u);
        return 0;
}