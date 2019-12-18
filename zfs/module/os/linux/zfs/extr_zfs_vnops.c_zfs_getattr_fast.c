#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ z_id; scalar_t__ z_blksz; int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_sa_hdl; } ;
typedef  TYPE_3__ znode_t ;
struct TYPE_14__ {scalar_t__ z_root; int /*<<< orphan*/  z_os; scalar_t__ z_issnap; int /*<<< orphan*/  z_max_blksz; } ;
typedef  TYPE_4__ zfsvfs_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct kstat {scalar_t__ nlink; scalar_t__ ino; int /*<<< orphan*/  blksize; int /*<<< orphan*/  blocks; } ;
struct inode {TYPE_2__* i_sb; } ;
struct TYPE_12__ {TYPE_1__* s_root; } ;
struct TYPE_11__ {struct inode* d_inode; } ;

/* Variables and functions */
 TYPE_3__* ITOZ (struct inode*) ; 
 TYPE_4__* ITOZSB (struct inode*) ; 
 scalar_t__ ZFSCTL_INO_SNAPDIRS ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_4__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_4__*) ; 
 scalar_t__ ZFS_LINK_MAX ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_3__*) ; 
 scalar_t__ dmu_objset_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_object_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ zfs_show_ctldir (TYPE_3__*) ; 

int
zfs_getattr_fast(struct inode *ip, struct kstat *sp)
{
	znode_t *zp = ITOZ(ip);
	zfsvfs_t *zfsvfs = ITOZSB(ip);
	uint32_t blksize;
	u_longlong_t nblocks;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	mutex_enter(&zp->z_lock);

	generic_fillattr(ip, sp);
	/*
	 * +1 link count for root inode with visible '.zfs' directory.
	 */
	if ((zp->z_id == zfsvfs->z_root) && zfs_show_ctldir(zp))
		if (sp->nlink < ZFS_LINK_MAX)
			sp->nlink++;

	sa_object_size(zp->z_sa_hdl, &blksize, &nblocks);
	sp->blksize = blksize;
	sp->blocks = nblocks;

	if (unlikely(zp->z_blksz == 0)) {
		/*
		 * Block size hasn't been set; suggest maximal I/O transfers.
		 */
		sp->blksize = zfsvfs->z_max_blksz;
	}

	mutex_exit(&zp->z_lock);

	/*
	 * Required to prevent NFS client from detecting different inode
	 * numbers of snapshot root dentry before and after snapshot mount.
	 */
	if (zfsvfs->z_issnap) {
		if (ip->i_sb->s_root->d_inode == ip)
			sp->ino = ZFSCTL_INO_SNAPDIRS -
			    dmu_objset_id(zfsvfs->z_os);
	}

	ZFS_EXIT(zfsvfs);

	return (0);
}