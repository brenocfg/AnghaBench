#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  slice; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  CGroupMask ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_DEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_get_members_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_get_subtree_mask (TYPE_1__*) ; 

CGroupMask unit_get_siblings_mask(Unit *u) {
        assert(u);

        /* Returns the mask of controllers all of the unit's siblings
         * require, i.e. the members mask of the unit's parent slice
         * if there is one. */

        if (UNIT_ISSET(u->slice))
                return unit_get_members_mask(UNIT_DEREF(u->slice));

        return unit_get_subtree_mask(u); /* we are the top-level slice */
}