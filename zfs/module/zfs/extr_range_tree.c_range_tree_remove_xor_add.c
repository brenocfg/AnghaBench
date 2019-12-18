#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_btree_index_t ;
struct TYPE_9__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_1__ range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_t ;

/* Variables and functions */
 int /*<<< orphan*/  range_tree_remove_xor_add_segment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rs_get_end (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rs_get_start (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zfs_btree_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_btree_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
range_tree_remove_xor_add(range_tree_t *rt, range_tree_t *removefrom,
    range_tree_t *addto)
{
	zfs_btree_index_t where;
	for (range_seg_t *rs = zfs_btree_first(&rt->rt_root, &where); rs;
	    rs = zfs_btree_next(&rt->rt_root, &where, &where)) {
		range_tree_remove_xor_add_segment(rs_get_start(rs, rt),
		    rs_get_end(rs, rt), removefrom, addto);
	}
}