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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {int /*<<< orphan*/  delegate_controllers; } ;
typedef  int /*<<< orphan*/  ExecContext ;
typedef  int /*<<< orphan*/  CGroupMask ;
typedef  TYPE_1__ CGroupContext ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_MASK_EXTEND_JOINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (TYPE_1__*) ; 
 scalar_t__ cg_all_unified () ; 
 int /*<<< orphan*/  exec_context_maintains_privileges (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_cgroup_delegate (int /*<<< orphan*/ *) ; 
 TYPE_1__* unit_get_cgroup_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * unit_get_exec_context (int /*<<< orphan*/ *) ; 

CGroupMask unit_get_delegate_mask(Unit *u) {
        CGroupContext *c;

        /* If delegation is turned on, then turn on selected controllers, unless we are on the legacy hierarchy and the
         * process we fork into is known to drop privileges, and hence shouldn't get access to the controllers.
         *
         * Note that on the unified hierarchy it is safe to delegate controllers to unprivileged services. */

        if (!unit_cgroup_delegate(u))
                return 0;

        if (cg_all_unified() <= 0) {
                ExecContext *e;

                e = unit_get_exec_context(u);
                if (e && !exec_context_maintains_privileges(e))
                        return 0;
        }

        assert_se(c = unit_get_cgroup_context(u));
        return CGROUP_MASK_EXTEND_JOINED(c->delegate_controllers);
}