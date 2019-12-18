#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bt_height; int /*<<< orphan*/ * bt_bulk; scalar_t__ bt_num_nodes; int /*<<< orphan*/ * bt_root; scalar_t__ bt_num_elems; } ;
typedef  TYPE_1__ zfs_btree_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (scalar_t__) ; 
 int /*<<< orphan*/  zfs_btree_clear_helper (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
zfs_btree_clear(zfs_btree_t *tree)
{
	if (tree->bt_root == NULL) {
		ASSERT0(tree->bt_num_elems);
		return;
	}

	zfs_btree_clear_helper(tree, tree->bt_root);
	tree->bt_num_elems = 0;
	tree->bt_root = NULL;
	tree->bt_num_nodes = 0;
	tree->bt_height = -1;
	tree->bt_bulk = NULL;
}