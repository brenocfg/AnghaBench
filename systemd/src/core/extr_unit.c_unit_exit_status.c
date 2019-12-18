#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_2__ {int (* exit_status ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_1__* UNIT_VTABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *) ; 

int unit_exit_status(Unit *u) {
        assert(u);

        /* Returns the exit status to propagate for the most recent cycle of this unit. Returns a value in the range
         * 0…255 if there's something to propagate. EOPNOTSUPP if the concept does not apply to this unit type, ENODATA
         * if no data is currently known (for example because the unit hasn't deactivated yet) and EBADE if the main
         * service process has exited abnormally (signal/coredump). */

        if (!UNIT_VTABLE(u)->exit_status)
                return -EOPNOTSUPP;

        return UNIT_VTABLE(u)->exit_status(u);
}