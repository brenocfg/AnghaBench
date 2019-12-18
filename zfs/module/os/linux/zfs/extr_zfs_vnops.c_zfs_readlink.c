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
struct TYPE_5__ {int /*<<< orphan*/  z_lock; int /*<<< orphan*/  z_sa_hdl; scalar_t__ z_is_sa; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  uio_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 TYPE_1__* ITOZ (struct inode*) ; 
 int /*<<< orphan*/ * ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  SA_ZPL_SYMLINK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int sa_lookup_uio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_sa_readlink (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
zfs_readlink(struct inode *ip, uio_t *uio, cred_t *cr)
{
	znode_t		*zp = ITOZ(ip);
	zfsvfs_t	*zfsvfs = ITOZSB(ip);
	int		error;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	mutex_enter(&zp->z_lock);
	if (zp->z_is_sa)
		error = sa_lookup_uio(zp->z_sa_hdl,
		    SA_ZPL_SYMLINK(zfsvfs), uio);
	else
		error = zfs_sa_readlink(zp, uio);
	mutex_exit(&zp->z_lock);

	ZFS_EXIT(zfsvfs);
	return (error);
}