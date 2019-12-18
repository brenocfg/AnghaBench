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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_btree_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_btree_numnodes (int /*<<< orphan*/ *) ; 

void
rt_btree_destroy(range_tree_t *rt, void *arg)
{
	zfs_btree_t *size_tree = arg;
	ASSERT0(zfs_btree_numnodes(size_tree));

	zfs_btree_destroy(size_tree);
}