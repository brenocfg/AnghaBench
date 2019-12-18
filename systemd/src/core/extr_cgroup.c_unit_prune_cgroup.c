#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int cgroup_realized; int /*<<< orphan*/  bpf_device_control_installed; scalar_t__ cgroup_enabled_mask; scalar_t__ cgroup_realized_mask; int /*<<< orphan*/  cgroup_path; TYPE_1__* manager; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_9__ {int /*<<< orphan*/  cgroup_supported; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SPECIAL_ROOT_SLICE ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  bpf_program_unref (int /*<<< orphan*/ ) ; 
 int cg_trim_everywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_full (TYPE_2__*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_get_cpu_usage (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int unit_has_name (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_release_cgroup (TYPE_2__*) ; 

void unit_prune_cgroup(Unit *u) {
        int r;
        bool is_root_slice;

        assert(u);

        /* Removes the cgroup, if empty and possible, and stops watching it. */

        if (!u->cgroup_path)
                return;

        (void) unit_get_cpu_usage(u, NULL); /* Cache the last CPU usage value before we destroy the cgroup */

        is_root_slice = unit_has_name(u, SPECIAL_ROOT_SLICE);

        r = cg_trim_everywhere(u->manager->cgroup_supported, u->cgroup_path, !is_root_slice);
        if (r < 0)
                /* One reason we could have failed here is, that the cgroup still contains a process.
                 * However, if the cgroup becomes removable at a later time, it might be removed when
                 * the containing slice is stopped. So even if we failed now, this unit shouldn't assume
                 * that the cgroup is still realized the next time it is started. Do not return early
                 * on error, continue cleanup. */
                log_unit_full(u, r == -EBUSY ? LOG_DEBUG : LOG_WARNING, r, "Failed to destroy cgroup %s, ignoring: %m", u->cgroup_path);

        if (is_root_slice)
                return;

        unit_release_cgroup(u);

        u->cgroup_realized = false;
        u->cgroup_realized_mask = 0;
        u->cgroup_enabled_mask = 0;

        u->bpf_device_control_installed = bpf_program_unref(u->bpf_device_control_installed);
}