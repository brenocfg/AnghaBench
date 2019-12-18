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
typedef  int /*<<< orphan*/  zfs_btree_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfs_btree_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
rt_btree_add(range_tree_t *rt, range_seg_t *rs, void *arg)
{
	zfs_btree_t *size_tree = arg;

	zfs_btree_add(size_tree, rs);
}