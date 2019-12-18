#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  slice; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  CGroupMask ;

/* Variables and functions */
 TYPE_1__* UNIT_DEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_get_disable_mask (TYPE_1__*) ; 

CGroupMask unit_get_ancestor_disable_mask(Unit *u) {
        CGroupMask mask;

        assert(u);
        mask = unit_get_disable_mask(u);

        /* Returns the mask of controllers which are marked as forcibly
         * disabled in any ancestor unit or the unit in question. */

        if (UNIT_ISSET(u->slice))
                mask |= unit_get_ancestor_disable_mask(UNIT_DEREF(u->slice));

        return mask;
}