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
typedef  int /*<<< orphan*/  zfs_btree_index_t ;
struct TYPE_5__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_1__ range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  rs_get_end (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rs_get_start (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  space_reftree_add_seg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_btree_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_btree_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
space_reftree_add_map(avl_tree_t *t, range_tree_t *rt, int64_t refcnt)
{
	zfs_btree_index_t where;

	for (range_seg_t *rs = zfs_btree_first(&rt->rt_root, &where); rs; rs =
	    zfs_btree_next(&rt->rt_root, &where, &where)) {
		space_reftree_add_seg(t, rs_get_start(rs, rt), rs_get_end(rs,
		    rt),  refcnt);
	}
}