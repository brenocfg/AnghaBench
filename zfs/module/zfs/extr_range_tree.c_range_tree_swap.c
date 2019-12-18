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
struct TYPE_5__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_1__ range_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_space (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_btree_numnodes (int /*<<< orphan*/ *) ; 

void
range_tree_swap(range_tree_t **rtsrc, range_tree_t **rtdst)
{
	range_tree_t *rt;

	ASSERT0(range_tree_space(*rtdst));
	ASSERT0(zfs_btree_numnodes(&(*rtdst)->rt_root));

	rt = *rtsrc;
	*rtsrc = *rtdst;
	*rtdst = rt;
}