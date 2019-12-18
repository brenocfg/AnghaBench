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
struct TYPE_5__ {int bt_height; int /*<<< orphan*/ * bt_bulk; scalar_t__ bt_num_elems; int /*<<< orphan*/ * bt_root; } ;
typedef  TYPE_1__ zfs_btree_t ;
typedef  int /*<<< orphan*/  zfs_btree_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/ * kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 void* zfs_btree_first (TYPE_1__*,int /*<<< orphan*/ *) ; 
 void* zfs_btree_next_helper (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_btree_node_destroy ; 

void *
zfs_btree_destroy_nodes(zfs_btree_t *tree, zfs_btree_index_t **cookie)
{
	if (*cookie == NULL) {
		if (tree->bt_height == -1)
			return (NULL);
		*cookie = kmem_alloc(sizeof (**cookie), KM_SLEEP);
		return (zfs_btree_first(tree, *cookie));
	}

	void *rval = zfs_btree_next_helper(tree, *cookie, *cookie,
	    zfs_btree_node_destroy);
	if (rval == NULL)   {
		tree->bt_root = NULL;
		tree->bt_height = -1;
		tree->bt_num_elems = 0;
		kmem_free(*cookie, sizeof (**cookie));
		tree->bt_bulk = NULL;
	}
	return (rval);
}