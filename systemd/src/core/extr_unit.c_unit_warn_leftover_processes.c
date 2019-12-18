#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cgroup_path; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int cg_kill_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  log_leftover ; 
 int /*<<< orphan*/  unit_pick_cgroup_path (TYPE_1__*) ; 

int unit_warn_leftover_processes(Unit *u) {
        assert(u);

        (void) unit_pick_cgroup_path(u);

        if (!u->cgroup_path)
                return 0;

        return cg_kill_recursive(SYSTEMD_CGROUP_CONTROLLER, u->cgroup_path, 0, 0, NULL, log_leftover, u);
}