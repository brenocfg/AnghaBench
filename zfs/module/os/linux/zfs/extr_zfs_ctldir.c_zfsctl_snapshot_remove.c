#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_snapentry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/  zfs_snapshots_by_name ; 
 int /*<<< orphan*/  zfs_snapshots_by_objsetid ; 
 int /*<<< orphan*/  zfsctl_snapshot_rele (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zfsctl_snapshot_remove(zfs_snapentry_t *se)
{
	ASSERT(RW_WRITE_HELD(&zfs_snapshot_lock));
	avl_remove(&zfs_snapshots_by_name, se);
	avl_remove(&zfs_snapshots_by_objsetid, se);
	zfsctl_snapshot_rele(se);
}