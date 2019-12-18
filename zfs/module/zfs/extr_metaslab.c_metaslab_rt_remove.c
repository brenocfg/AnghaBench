#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_btree_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_t ;
struct TYPE_2__ {int mra_floor_shift; int /*<<< orphan*/ * mra_bt; } ;
typedef  TYPE_1__ metaslab_rt_arg_t ;

/* Variables and functions */
 int rs_get_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rs_get_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_btree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
metaslab_rt_remove(range_tree_t *rt, range_seg_t *rs, void *arg)
{
	metaslab_rt_arg_t *mrap = arg;
	zfs_btree_t *size_tree = mrap->mra_bt;

	if (rs_get_end(rs, rt) - rs_get_start(rs, rt) < (1 <<
	    mrap->mra_floor_shift))
		return;

	zfs_btree_remove(size_tree, rs);
}