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
typedef  int /*<<< orphan*/  zfs_btree_hdr_t ;
struct TYPE_6__ {int /*<<< orphan*/  bth_core; } ;
struct TYPE_8__ {int /*<<< orphan*/ ** btc_children; int /*<<< orphan*/ ** btc_elems; TYPE_1__ btc_hdr; } ;
typedef  TYPE_3__ zfs_btree_core_t ;
typedef  int /*<<< orphan*/ * uint8_t ;
typedef  size_t uint64_t ;
typedef  enum bt_shift_shape { ____Placeholder_bt_shift_shape } bt_shift_shape ;
typedef  enum bt_shift_direction { ____Placeholder_bt_shift_direction } bt_shift_direction ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int BSD_LEFT ; 
 int BSS_TRAPEZOID ; 
 int /*<<< orphan*/  bmov (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t) ; 

__attribute__((used)) static inline void
bt_shift_core(zfs_btree_t *tree, zfs_btree_core_t *node, uint64_t idx,
    uint64_t count, uint64_t off, enum bt_shift_shape shape,
    enum bt_shift_direction dir)
{
	size_t size = tree->bt_elem_size;
	ASSERT(node->btc_hdr.bth_core);

	uint8_t *e_start = node->btc_elems + idx * size;
	int sign = (dir == BSD_LEFT ? -1 : +1);
	uint8_t *e_out = e_start + sign * off * size;
	uint64_t e_count = count;
	bmov(e_start, e_out, e_count * size);

	zfs_btree_hdr_t **c_start = node->btc_children + idx +
	    (shape == BSS_TRAPEZOID ? 0 : 1);
	zfs_btree_hdr_t **c_out = (dir == BSD_LEFT ? c_start - off :
	    c_start + off);
	uint64_t c_count = count + (shape == BSS_TRAPEZOID ? 1 : 0);
	bmov(c_start, c_out, c_count * sizeof (*c_start));
}