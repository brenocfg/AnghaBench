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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_1__ range_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfs_btree_numnodes (int /*<<< orphan*/ *) ; 

uint64_t
range_tree_numsegs(range_tree_t *rt)
{
	return ((rt == NULL) ? 0 : zfs_btree_numnodes(&rt->rt_root));
}