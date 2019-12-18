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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/ * zfsctl_snapshot_find_by_objsetid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsctl_snapshot_rele (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsctl_snapshot_unmount_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsctl_snapshot_unmount_delay_impl (int /*<<< orphan*/ *,int) ; 

int
zfsctl_snapshot_unmount_delay(spa_t *spa, uint64_t objsetid, int delay)
{
	zfs_snapentry_t *se;
	int error = ENOENT;

	rw_enter(&zfs_snapshot_lock, RW_READER);
	if ((se = zfsctl_snapshot_find_by_objsetid(spa, objsetid)) != NULL) {
		zfsctl_snapshot_unmount_cancel(se);
		zfsctl_snapshot_unmount_delay_impl(se, delay);
		zfsctl_snapshot_rele(se);
		error = 0;
	}
	rw_exit(&zfs_snapshot_lock);

	return (error);
}