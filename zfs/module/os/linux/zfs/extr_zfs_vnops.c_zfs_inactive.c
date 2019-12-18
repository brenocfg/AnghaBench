#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ z_unlinked; int /*<<< orphan*/  z_lock; scalar_t__ z_atime_dirty; int /*<<< orphan*/ * z_sa_hdl; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_9__ {int /*<<< orphan*/  z_teardown_inactive_lock; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct inode {int /*<<< orphan*/  i_atime; } ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  atime ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 TYPE_2__* ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SA_ZPL_ATIME (TYPE_2__*) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  ZFS_TIME_ENCODE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_sa_upgrade_txholds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_zinactive (TYPE_1__*) ; 

void
zfs_inactive(struct inode *ip)
{
	znode_t	*zp = ITOZ(ip);
	zfsvfs_t *zfsvfs = ITOZSB(ip);
	uint64_t atime[2];
	int error;
	int need_unlock = 0;

	/* Only read lock if we haven't already write locked, e.g. rollback */
	if (!RW_WRITE_HELD(&zfsvfs->z_teardown_inactive_lock)) {
		need_unlock = 1;
		rw_enter(&zfsvfs->z_teardown_inactive_lock, RW_READER);
	}
	if (zp->z_sa_hdl == NULL) {
		if (need_unlock)
			rw_exit(&zfsvfs->z_teardown_inactive_lock);
		return;
	}

	if (zp->z_atime_dirty && zp->z_unlinked == B_FALSE) {
		dmu_tx_t *tx = dmu_tx_create(zfsvfs->z_os);

		dmu_tx_hold_sa(tx, zp->z_sa_hdl, B_FALSE);
		zfs_sa_upgrade_txholds(tx, zp);
		error = dmu_tx_assign(tx, TXG_WAIT);
		if (error) {
			dmu_tx_abort(tx);
		} else {
			ZFS_TIME_ENCODE(&ip->i_atime, atime);
			mutex_enter(&zp->z_lock);
			(void) sa_update(zp->z_sa_hdl, SA_ZPL_ATIME(zfsvfs),
			    (void *)&atime, sizeof (atime), tx);
			zp->z_atime_dirty = B_FALSE;
			mutex_exit(&zp->z_lock);
			dmu_tx_commit(tx);
		}
	}

	zfs_zinactive(zp);
	if (need_unlock)
		rw_exit(&zfsvfs->z_teardown_inactive_lock);
}