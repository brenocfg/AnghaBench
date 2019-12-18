#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  ManagerState ;
typedef  int /*<<< orphan*/  CGroupContext ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_WEIGHT_DEFAULT ; 
 int /*<<< orphan*/  cgroup_context_cpu_weight (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * unit_get_cgroup_context (TYPE_1__*) ; 

__attribute__((used)) static uint64_t unit_get_cpu_weight(Unit *u) {
        ManagerState state = manager_state(u->manager);
        CGroupContext *cc;

        cc = unit_get_cgroup_context(u);
        return cc ? cgroup_context_cpu_weight(cc, state) : CGROUP_WEIGHT_DEFAULT;
}