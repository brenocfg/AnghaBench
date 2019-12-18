#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * z_ctldir; TYPE_3__* z_os; scalar_t__ z_issnap; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zfs_snapentry_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_5__ {int /*<<< orphan*/ * os_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  dmu_objset_id (TYPE_3__*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/ * zfsctl_snapshot_find_by_objsetid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsctl_snapshot_rele (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsctl_snapshot_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsctl_snapshot_unmount_cancel (int /*<<< orphan*/ *) ; 

void
zfsctl_destroy(zfsvfs_t *zfsvfs)
{
	if (zfsvfs->z_issnap) {
		zfs_snapentry_t *se;
		spa_t *spa = zfsvfs->z_os->os_spa;
		uint64_t objsetid = dmu_objset_id(zfsvfs->z_os);

		rw_enter(&zfs_snapshot_lock, RW_WRITER);
		se = zfsctl_snapshot_find_by_objsetid(spa, objsetid);
		if (se != NULL)
			zfsctl_snapshot_remove(se);
		rw_exit(&zfs_snapshot_lock);
		if (se != NULL) {
			zfsctl_snapshot_unmount_cancel(se);
			zfsctl_snapshot_rele(se);
		}
	} else if (zfsvfs->z_ctldir) {
		iput(zfsvfs->z_ctldir);
		zfsvfs->z_ctldir = NULL;
	}
}