#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t bt_elem_size; } ;
typedef  TYPE_2__ zfs_btree_t ;
struct TYPE_6__ {int /*<<< orphan*/  bth_core; } ;
struct TYPE_8__ {int /*<<< orphan*/ * btl_elems; TYPE_1__ btl_hdr; } ;
typedef  TYPE_3__ zfs_btree_leaf_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
typedef  enum bt_shift_direction { ____Placeholder_bt_shift_direction } bt_shift_direction ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BSD_LEFT ; 
 int /*<<< orphan*/  bmov (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static inline void
bt_shift_leaf(zfs_btree_t *tree, zfs_btree_leaf_t *node, uint64_t idx,
    uint64_t count, uint64_t off, enum bt_shift_direction dir)
{
	size_t size = tree->bt_elem_size;
	ASSERT(!node->btl_hdr.bth_core);

	uint8_t *start = node->btl_elems + idx * size;
	int sign = (dir == BSD_LEFT ? -1 : +1);
	uint8_t *out = start + sign * off * size;
	bmov(start, out, count * size);
}