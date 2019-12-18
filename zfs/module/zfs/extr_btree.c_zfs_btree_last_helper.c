#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int bt_elem_size; } ;
typedef  TYPE_1__ zfs_btree_t ;
struct TYPE_10__ {void* btl_elems; } ;
typedef  TYPE_2__ zfs_btree_leaf_t ;
struct TYPE_11__ {int bti_offset; int /*<<< orphan*/  bti_before; TYPE_4__* bti_node; } ;
typedef  TYPE_3__ zfs_btree_index_t ;
struct TYPE_12__ {size_t bth_count; scalar_t__ bth_core; } ;
typedef  TYPE_4__ zfs_btree_hdr_t ;
struct TYPE_13__ {TYPE_4__** btc_children; } ;
typedef  TYPE_5__ zfs_btree_core_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 

__attribute__((used)) static void *
zfs_btree_last_helper(zfs_btree_t *btree, zfs_btree_hdr_t *hdr,
    zfs_btree_index_t *where)
{
	zfs_btree_hdr_t *node;

	for (node = hdr; node->bth_core; node =
	    ((zfs_btree_core_t *)node)->btc_children[node->bth_count])
		;

	zfs_btree_leaf_t *leaf = (zfs_btree_leaf_t *)node;
	if (where != NULL) {
		where->bti_node = node;
		where->bti_offset = node->bth_count - 1;
		where->bti_before = B_FALSE;
	}
	return (leaf->btl_elems + (node->bth_count - 1) * btree->bt_elem_size);
}