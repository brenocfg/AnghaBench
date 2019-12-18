#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int bt_elem_size; } ;
typedef  TYPE_2__ zfs_btree_t ;
struct TYPE_10__ {void* btl_elems; } ;
typedef  TYPE_3__ zfs_btree_leaf_t ;
struct TYPE_11__ {int bti_offset; TYPE_1__* bti_node; int /*<<< orphan*/  bti_before; } ;
typedef  TYPE_4__ zfs_btree_index_t ;
struct TYPE_12__ {void* btc_elems; } ;
typedef  TYPE_5__ zfs_btree_core_t ;
struct TYPE_8__ {int bth_core; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

void *
zfs_btree_get(zfs_btree_t *tree, zfs_btree_index_t *idx)
{
	ASSERT(!idx->bti_before);
	if (!idx->bti_node->bth_core) {
		zfs_btree_leaf_t *leaf = (zfs_btree_leaf_t *)idx->bti_node;
		return (leaf->btl_elems + idx->bti_offset * tree->bt_elem_size);
	}
	ASSERT(idx->bti_node->bth_core);
	zfs_btree_core_t *node = (zfs_btree_core_t *)idx->bti_node;
	return (node->btc_elems + idx->bti_offset * tree->bt_elem_size);
}