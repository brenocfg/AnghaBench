#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_HAS_CGROUP_CONTEXT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_add_siblings_to_cgroup_realize_queue (TYPE_1__*) ; 
 int unit_realize_cgroup_now (TYPE_1__*,int /*<<< orphan*/ ) ; 

int unit_realize_cgroup(Unit *u) {
        assert(u);

        if (!UNIT_HAS_CGROUP_CONTEXT(u))
                return 0;

        /* So, here's the deal: when realizing the cgroups for this
         * unit, we need to first create all parents, but there's more
         * actually: for the weight-based controllers we also need to
         * make sure that all our siblings (i.e. units that are in the
         * same slice as we are) have cgroups, too. Otherwise, things
         * would become very uneven as each of their processes would
         * get as much resources as all our group together. This call
         * will synchronously create the parent cgroups, but will
         * defer work on the siblings to the next event loop
         * iteration. */

        /* Add all sibling slices to the cgroup queue. */
        unit_add_siblings_to_cgroup_realize_queue(u);

        /* And realize this one now (and apply the values) */
        return unit_realize_cgroup_now(u, manager_state(u->manager));
}