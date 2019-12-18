#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t bt_elem_size; } ;
typedef  TYPE_1__ zfs_btree_t ;
struct TYPE_8__ {scalar_t__ btl_elems; } ;
typedef  TYPE_2__ zfs_btree_leaf_t ;
struct TYPE_9__ {size_t bth_count; int /*<<< orphan*/  bth_core; } ;
typedef  TYPE_3__ zfs_btree_hdr_t ;
struct TYPE_10__ {scalar_t__ btc_elems; TYPE_3__** btc_children; } ;
typedef  TYPE_4__ zfs_btree_core_t ;

/* Variables and functions */
 int BTREE_CORE_ELEMS ; 
 int BTREE_LEAF_SIZE ; 
 scalar_t__ BTREE_POISON ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

__attribute__((used)) static void
zfs_btree_poison_node(zfs_btree_t *tree, zfs_btree_hdr_t *hdr)
{
#ifdef ZFS_DEBUG
	size_t size = tree->bt_elem_size;
	if (!hdr->bth_core) {
		zfs_btree_leaf_t *leaf = (zfs_btree_leaf_t *)hdr;
		(void) memset(leaf->btl_elems + hdr->bth_count * size, 0x0f,
		    BTREE_LEAF_SIZE - sizeof (zfs_btree_hdr_t) -
		    hdr->bth_count * size);
	} else {
		zfs_btree_core_t *node = (zfs_btree_core_t *)hdr;
		for (int i = hdr->bth_count + 1; i <= BTREE_CORE_ELEMS; i++) {
			node->btc_children[i] =
			    (zfs_btree_hdr_t *)BTREE_POISON;
		}
		(void) memset(node->btc_elems + hdr->bth_count * size, 0x0f,
		    (BTREE_CORE_ELEMS - hdr->bth_count) * size);
	}
#endif
}