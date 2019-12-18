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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  range_seg_t ;
struct TYPE_3__ {int /*<<< orphan*/  ms_allocatable; int /*<<< orphan*/  ms_allocatable_by_size; } ;
typedef  TYPE_1__ metaslab_t ;

/* Variables and functions */
 int /*<<< orphan*/  metaslab_size_tree_full_load (int /*<<< orphan*/ ) ; 
 scalar_t__ rs_get_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rs_get_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_btree_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_btree_numnodes (int /*<<< orphan*/ *) ; 

uint64_t
metaslab_largest_allocatable(metaslab_t *msp)
{
	zfs_btree_t *t = &msp->ms_allocatable_by_size;
	range_seg_t *rs;

	if (t == NULL)
		return (0);
	if (zfs_btree_numnodes(t) == 0)
		metaslab_size_tree_full_load(msp->ms_allocatable);

	rs = zfs_btree_last(t, NULL);
	if (rs == NULL)
		return (0);

	return (rs_get_end(rs, msp->ms_allocatable) - rs_get_start(rs,
	    msp->ms_allocatable));
}