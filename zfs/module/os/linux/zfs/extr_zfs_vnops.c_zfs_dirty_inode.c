#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/ ******** z_mode; int /*<<< orphan*/  z_atime_dirty; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_15__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/ **** uint64_t ;
struct inode {int /*<<< orphan*/ ******** i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 TYPE_2__* ITOZSB (struct inode*) ; 
 int I_DIRTY_TIME ; 
 int /*<<< orphan*/  SA_ADD_BULK_ATTR (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ******,int) ; 
 int /*<<< orphan*/  SA_ZPL_ATIME (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_CTIME (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_MODE (TYPE_2__*) ; 
 int /*<<< orphan*/  SA_ZPL_MTIME (TYPE_2__*) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_TIME_ENCODE (int /*<<< orphan*/ *,int /*<<< orphan*/ *****) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 scalar_t__ dmu_objset_is_snapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_sa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int sa_bulk_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_is_readonly (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_sa_upgrade_txholds (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
zfs_dirty_inode(struct inode *ip, int flags)
{
	znode_t		*zp = ITOZ(ip);
	zfsvfs_t	*zfsvfs = ITOZSB(ip);
	dmu_tx_t	*tx;
	uint64_t	mode, atime[2], mtime[2], ctime[2];
	sa_bulk_attr_t	bulk[4];
	int		error = 0;
	int		cnt = 0;

	if (zfs_is_readonly(zfsvfs) || dmu_objset_is_snapshot(zfsvfs->z_os))
		return (0);

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

#ifdef I_DIRTY_TIME
	/*
	 * This is the lazytime semantic introduced in Linux 4.0
	 * This flag will only be called from update_time when lazytime is set.
	 * (Note, I_DIRTY_SYNC will also set if not lazytime)
	 * Fortunately mtime and ctime are managed within ZFS itself, so we
	 * only need to dirty atime.
	 */
	if (flags == I_DIRTY_TIME) {
		zp->z_atime_dirty = B_TRUE;
		goto out;
	}
#endif

	tx = dmu_tx_create(zfsvfs->z_os);

	dmu_tx_hold_sa(tx, zp->z_sa_hdl, B_FALSE);
	zfs_sa_upgrade_txholds(tx, zp);

	error = dmu_tx_assign(tx, TXG_WAIT);
	if (error) {
		dmu_tx_abort(tx);
		goto out;
	}

	mutex_enter(&zp->z_lock);
	zp->z_atime_dirty = B_FALSE;

	SA_ADD_BULK_ATTR(bulk, cnt, SA_ZPL_MODE(zfsvfs), NULL, &mode, 8);
	SA_ADD_BULK_ATTR(bulk, cnt, SA_ZPL_ATIME(zfsvfs), NULL, &atime, 16);
	SA_ADD_BULK_ATTR(bulk, cnt, SA_ZPL_MTIME(zfsvfs), NULL, &mtime, 16);
	SA_ADD_BULK_ATTR(bulk, cnt, SA_ZPL_CTIME(zfsvfs), NULL, &ctime, 16);

	/* Preserve the mode, mtime and ctime provided by the inode */
	ZFS_TIME_ENCODE(&ip->i_atime, atime);
	ZFS_TIME_ENCODE(&ip->i_mtime, mtime);
	ZFS_TIME_ENCODE(&ip->i_ctime, ctime);
	mode = ip->i_mode;

	zp->z_mode = mode;

	error = sa_bulk_update(zp->z_sa_hdl, bulk, cnt, tx);
	mutex_exit(&zp->z_lock);

	dmu_tx_commit(tx);
out:
	ZFS_EXIT(zfsvfs);
	return (error);
}