#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ type; int /*<<< orphan*/  slice; scalar_t__ cgroup_realized; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  SPECIAL_INIT_SCOPE ; 
 int /*<<< orphan*/  SPECIAL_ROOT_SLICE ; 
 TYPE_1__* UNIT_DEREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_HAS_CGROUP_CONTEXT (TYPE_1__*) ; 
 scalar_t__ UNIT_INACTIVE ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_SLICE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ unit_active_state (TYPE_1__*) ; 
 scalar_t__ unit_has_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_ref_set (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

int unit_set_slice(Unit *u, Unit *slice) {
        assert(u);
        assert(slice);

        /* Sets the unit slice if it has not been set before. Is extra
         * careful, to only allow this for units that actually have a
         * cgroup context. Also, we don't allow to set this for slices
         * (since the parent slice is derived from the name). Make
         * sure the unit we set is actually a slice. */

        if (!UNIT_HAS_CGROUP_CONTEXT(u))
                return -EOPNOTSUPP;

        if (u->type == UNIT_SLICE)
                return -EINVAL;

        if (unit_active_state(u) != UNIT_INACTIVE)
                return -EBUSY;

        if (slice->type != UNIT_SLICE)
                return -EINVAL;

        if (unit_has_name(u, SPECIAL_INIT_SCOPE) &&
            !unit_has_name(slice, SPECIAL_ROOT_SLICE))
                return -EPERM;

        if (UNIT_DEREF(u->slice) == slice)
                return 0;

        /* Disallow slice changes if @u is already bound to cgroups */
        if (UNIT_ISSET(u->slice) && u->cgroup_realized)
                return -EBUSY;

        unit_ref_set(&u->slice, u, slice);
        return 1;
}