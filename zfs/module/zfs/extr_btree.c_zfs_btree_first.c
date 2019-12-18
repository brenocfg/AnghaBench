#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bt_height; int /*<<< orphan*/  bt_root; int /*<<< orphan*/  bt_num_elems; } ;
typedef  TYPE_1__ zfs_btree_t ;
typedef  int /*<<< orphan*/  zfs_btree_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 void* zfs_btree_first_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void *
zfs_btree_first(zfs_btree_t *tree, zfs_btree_index_t *where)
{
	if (tree->bt_height == -1) {
		ASSERT0(tree->bt_num_elems);
		return (NULL);
	}
	return (zfs_btree_first_helper(tree->bt_root, where));
}