#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnitActiveState ;
struct TYPE_8__ {scalar_t__ load_state; scalar_t__ job; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_9__ {int (* clean ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  ExecCleanMask ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int EUNATCH ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_INACTIVE ; 
 scalar_t__ UNIT_LOADED ; 
 TYPE_6__* UNIT_VTABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_active_state (TYPE_1__*) ; 

int unit_clean(Unit *u, ExecCleanMask mask) {
        UnitActiveState state;

        assert(u);

        /* Special return values:
         *
         *   -EOPNOTSUPP → cleaning not supported for this unit type
         *   -EUNATCH    → cleaning not defined for this resource type
         *   -EBUSY      → unit currently can't be cleaned since it's running or not properly loaded, or has
         *                 a job queued or similar
         */

        if (!UNIT_VTABLE(u)->clean)
                return -EOPNOTSUPP;

        if (mask == 0)
                return -EUNATCH;

        if (u->load_state != UNIT_LOADED)
                return -EBUSY;

        if (u->job)
                return -EBUSY;

        state = unit_active_state(u);
        if (!IN_SET(state, UNIT_INACTIVE))
                return -EBUSY;

        return UNIT_VTABLE(u)->clean(u, mask);
}