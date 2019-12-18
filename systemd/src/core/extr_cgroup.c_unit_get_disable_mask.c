#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_3__ {int /*<<< orphan*/  disable_controllers; } ;
typedef  int /*<<< orphan*/  CGroupMask ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 TYPE_1__* unit_get_cgroup_context (int /*<<< orphan*/ *) ; 

CGroupMask unit_get_disable_mask(Unit *u) {
        CGroupContext *c;

        c = unit_get_cgroup_context(u);
        if (!c)
                return 0;

        return c->disable_controllers;
}