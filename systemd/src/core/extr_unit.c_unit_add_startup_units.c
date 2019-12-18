#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* manager; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_10__ {scalar_t__ startup_cpu_shares; scalar_t__ startup_io_weight; scalar_t__ startup_blockio_weight; } ;
struct TYPE_8__ {int /*<<< orphan*/  startup_units; } ;
typedef  TYPE_3__ CGroupContext ;

/* Variables and functions */
 scalar_t__ CGROUP_BLKIO_WEIGHT_INVALID ; 
 scalar_t__ CGROUP_CPU_SHARES_INVALID ; 
 scalar_t__ CGROUP_WEIGHT_INVALID ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_3__* unit_get_cgroup_context (TYPE_2__*) ; 

__attribute__((used)) static int unit_add_startup_units(Unit *u) {
        CGroupContext *c;
        int r;

        c = unit_get_cgroup_context(u);
        if (!c)
                return 0;

        if (c->startup_cpu_shares == CGROUP_CPU_SHARES_INVALID &&
            c->startup_io_weight == CGROUP_WEIGHT_INVALID &&
            c->startup_blockio_weight == CGROUP_BLKIO_WEIGHT_INVALID)
                return 0;

        r = set_ensure_allocated(&u->manager->startup_units, NULL);
        if (r < 0)
                return r;

        return set_put(u->manager->startup_units, u);
}