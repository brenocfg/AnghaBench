#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int z_pflags; scalar_t__ z_size; int /*<<< orphan*/  z_sync_cnt; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_10__ {scalar_t__ z_vscan; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct inode {int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EPERM ; 
 int FMODE_WRITE ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 TYPE_2__* ITOZSB (struct inode*) ; 
 int O_APPEND ; 
 int O_SYNC ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int ZFS_APPENDONLY ; 
 int ZFS_AV_QUARANTINED ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_inc_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_has_ctldir (TYPE_1__*) ; 
 scalar_t__ zfs_vscan (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zfs_open(struct inode *ip, int mode, int flag, cred_t *cr)
{
	znode_t	*zp = ITOZ(ip);
	zfsvfs_t *zfsvfs = ITOZSB(ip);

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	/* Honor ZFS_APPENDONLY file attribute */
	if ((mode & FMODE_WRITE) && (zp->z_pflags & ZFS_APPENDONLY) &&
	    ((flag & O_APPEND) == 0)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EPERM));
	}

	/* Virus scan eligible files on open */
	if (!zfs_has_ctldir(zp) && zfsvfs->z_vscan && S_ISREG(ip->i_mode) &&
	    !(zp->z_pflags & ZFS_AV_QUARANTINED) && zp->z_size > 0) {
		if (zfs_vscan(ip, cr, 0) != 0) {
			ZFS_EXIT(zfsvfs);
			return (SET_ERROR(EACCES));
		}
	}

	/* Keep a count of the synchronous opens in the znode */
	if (flag & O_SYNC)
		atomic_inc_32(&zp->z_sync_cnt);

	ZFS_EXIT(zfsvfs);
	return (0);
}