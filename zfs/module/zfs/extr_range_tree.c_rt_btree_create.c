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
typedef  int /*<<< orphan*/  zfs_btree_t ;
struct TYPE_3__ {int rt_type; int /*<<< orphan*/  rt_btree_compare; } ;
typedef  TYPE_1__ range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_gap_t ;
typedef  int /*<<< orphan*/  range_seg64_t ;
typedef  int /*<<< orphan*/  range_seg32_t ;

/* Variables and functions */
#define  RANGE_SEG32 130 
#define  RANGE_SEG64 129 
#define  RANGE_SEG_GAP 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  zfs_btree_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

void
rt_btree_create(range_tree_t *rt, void *arg)
{
	zfs_btree_t *size_tree = arg;

	size_t size;
	switch (rt->rt_type) {
	case RANGE_SEG32:
		size = sizeof (range_seg32_t);
		break;
	case RANGE_SEG64:
		size = sizeof (range_seg64_t);
		break;
	case RANGE_SEG_GAP:
		size = sizeof (range_seg_gap_t);
		break;
	default:
		panic("Invalid range seg type %d", rt->rt_type);
	}
	zfs_btree_create(size_tree, rt->rt_btree_compare, size);
}