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
struct TYPE_5__ {int /*<<< orphan*/  se_name; int /*<<< orphan*/  se_taskqid; int /*<<< orphan*/  se_objsetid; int /*<<< orphan*/ * se_spa; } ;
typedef  TYPE_1__ zfs_snapentry_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_EXPIRE ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  TASKQID_INVALID ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_expire_snapshot ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 TYPE_1__* zfsctl_snapshot_find_by_objsetid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsctl_snapshot_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  zfsctl_snapshot_unmount (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsctl_snapshot_unmount_delay_impl (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
snapentry_expire(void *data)
{
	zfs_snapentry_t *se = (zfs_snapentry_t *)data;
	spa_t *spa = se->se_spa;
	uint64_t objsetid = se->se_objsetid;

	if (zfs_expire_snapshot <= 0) {
		zfsctl_snapshot_rele(se);
		return;
	}

	se->se_taskqid = TASKQID_INVALID;
	(void) zfsctl_snapshot_unmount(se->se_name, MNT_EXPIRE);
	zfsctl_snapshot_rele(se);

	/*
	 * Reschedule the unmount if the zfs_snapentry_t wasn't removed.
	 * This can occur when the snapshot is busy.
	 */
	rw_enter(&zfs_snapshot_lock, RW_READER);
	if ((se = zfsctl_snapshot_find_by_objsetid(spa, objsetid)) != NULL) {
		zfsctl_snapshot_unmount_delay_impl(se, zfs_expire_snapshot);
		zfsctl_snapshot_rele(se);
	}
	rw_exit(&zfs_snapshot_lock);
}