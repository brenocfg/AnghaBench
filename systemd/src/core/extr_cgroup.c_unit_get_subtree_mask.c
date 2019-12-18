#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
typedef  int CGroupMask ;

/* Variables and functions */
 int unit_get_members_mask (int /*<<< orphan*/ *) ; 
 int unit_get_own_mask (int /*<<< orphan*/ *) ; 

CGroupMask unit_get_subtree_mask(Unit *u) {

        /* Returns the mask of this subtree, meaning of the group
         * itself and its children. */

        return unit_get_own_mask(u) | unit_get_members_mask(u);
}