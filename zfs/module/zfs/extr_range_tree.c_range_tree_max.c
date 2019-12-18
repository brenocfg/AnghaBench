#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_1__ range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_t ;

/* Variables and functions */
 int /*<<< orphan*/  rs_get_end (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zfs_btree_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

uint64_t
range_tree_max(range_tree_t *rt)
{
	range_seg_t *rs = zfs_btree_last(&rt->rt_root, NULL);
	return (rs != NULL ? rs_get_end(rs, rt) : 0);
}