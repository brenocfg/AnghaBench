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

/* Variables and functions */
 int /*<<< orphan*/  zfs_btree_verify_counts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_btree_verify_height (int /*<<< orphan*/ *) ; 
 int zfs_btree_verify_intensity ; 
 int /*<<< orphan*/  zfs_btree_verify_order (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_btree_verify_pointers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_btree_verify_poison (int /*<<< orphan*/ *) ; 

void
zfs_btree_verify(zfs_btree_t *tree)
{
	if (zfs_btree_verify_intensity == 0)
		return;
	zfs_btree_verify_height(tree);
	if (zfs_btree_verify_intensity == 1)
		return;
	zfs_btree_verify_pointers(tree);
	if (zfs_btree_verify_intensity == 2)
		return;
	zfs_btree_verify_counts(tree);
	if (zfs_btree_verify_intensity == 3)
		return;
	zfs_btree_verify_order(tree);

	if (zfs_btree_verify_intensity == 4)
		return;
	zfs_btree_verify_poison(tree);
}