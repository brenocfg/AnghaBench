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
struct TYPE_2__ {int /*<<< orphan*/ * zn_handle; } ;
typedef  TYPE_1__ zfs_node_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int TREE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_CREATETXG ; 
 int /*<<< orphan*/  zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_snapshot_compare(const void *larg, const void *rarg)
{
	zfs_handle_t *l = ((zfs_node_t *)larg)->zn_handle;
	zfs_handle_t *r = ((zfs_node_t *)rarg)->zn_handle;
	uint64_t lcreate, rcreate;

	/*
	 * Sort them according to creation time.  We use the hidden
	 * CREATETXG property to get an absolute ordering of snapshots.
	 */
	lcreate = zfs_prop_get_int(l, ZFS_PROP_CREATETXG);
	rcreate = zfs_prop_get_int(r, ZFS_PROP_CREATETXG);

	return (TREE_CMP(lcreate, rcreate));
}