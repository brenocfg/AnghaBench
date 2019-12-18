#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {int cpu_accounting; int tasks_accounting; int memory_accounting; } ;
struct TYPE_5__ {TYPE_1__ cgroup_context; } ;
typedef  TYPE_2__ Slice ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 scalar_t__ MANAGER_IS_SYSTEM (int /*<<< orphan*/ *) ; 
 TYPE_2__* SLICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPECIAL_ROOT_SLICE ; 
 int /*<<< orphan*/  SPECIAL_SYSTEM_SLICE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ manager_owns_host_root_cgroup (int /*<<< orphan*/ *) ; 
 int slice_make_perpetual (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void slice_enumerate_perpetual(Manager *m) {
        Unit *u;
        int r;

        assert(m);

        r = slice_make_perpetual(m, SPECIAL_ROOT_SLICE, &u);
        if (r >= 0 && manager_owns_host_root_cgroup(m)) {
                Slice *s = SLICE(u);

                /* If we are managing the root cgroup then this means our root slice covers the whole system, which
                 * means the kernel will track CPU/tasks/memory for us anyway, and it is all available in /proc. Let's
                 * hence turn accounting on here, so that our APIs to query this data are available. */

                s->cgroup_context.cpu_accounting = true;
                s->cgroup_context.tasks_accounting = true;
                s->cgroup_context.memory_accounting = true;
        }

        if (MANAGER_IS_SYSTEM(m))
                (void) slice_make_perpetual(m, SPECIAL_SYSTEM_SLICE, NULL);
}