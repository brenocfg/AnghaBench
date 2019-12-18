#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ memory_high; scalar_t__ memory_max; scalar_t__ memory_swap_max; } ;
typedef  TYPE_1__ Unit ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 scalar_t__ CGROUP_LIMIT_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ unit_get_ancestor_memory_low (TYPE_1__*) ; 
 scalar_t__ unit_get_ancestor_memory_min (TYPE_1__*) ; 
 TYPE_1__* unit_get_cgroup_context (TYPE_1__*) ; 

__attribute__((used)) static bool unit_has_unified_memory_config(Unit *u) {
        CGroupContext *c;

        assert(u);

        c = unit_get_cgroup_context(u);
        assert(c);

        return unit_get_ancestor_memory_min(u) > 0 || unit_get_ancestor_memory_low(u) > 0 ||
               c->memory_high != CGROUP_LIMIT_MAX || c->memory_max != CGROUP_LIMIT_MAX ||
               c->memory_swap_max != CGROUP_LIMIT_MAX;
}