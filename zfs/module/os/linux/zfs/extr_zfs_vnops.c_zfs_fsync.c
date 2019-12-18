#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  z_id; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_11__ {int /*<<< orphan*/  z_log; TYPE_1__* z_os; } ;
typedef  TYPE_3__ zfsvfs_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_9__ {scalar_t__ os_sync; } ;

/* Variables and functions */
 TYPE_2__* ITOZ (struct inode*) ; 
 TYPE_3__* ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 scalar_t__ ZFS_SYNC_DISABLED ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_2__*) ; 
 int /*<<< orphan*/  tsd_set (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ zfs_fsync_sync_cnt ; 
 int /*<<< orphan*/  zfs_fsyncer_key ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_fsync(struct inode *ip, int syncflag, cred_t *cr)
{
	znode_t	*zp = ITOZ(ip);
	zfsvfs_t *zfsvfs = ITOZSB(ip);

	(void) tsd_set(zfs_fsyncer_key, (void *)zfs_fsync_sync_cnt);

	if (zfsvfs->z_os->os_sync != ZFS_SYNC_DISABLED) {
		ZFS_ENTER(zfsvfs);
		ZFS_VERIFY_ZP(zp);
		zil_commit(zfsvfs->z_log, zp->z_id);
		ZFS_EXIT(zfsvfs);
	}
	tsd_set(zfs_fsyncer_key, NULL);

	return (0);
}