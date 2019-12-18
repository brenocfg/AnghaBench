#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
struct TYPE_6__ {scalar_t__ z_shares_dir; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  pathname_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 TYPE_1__* ITOZSB (struct inode*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_1__*) ; 
 int /*<<< orphan*/  ZTOI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int zfs_lookup (int /*<<< orphan*/ ,char*,struct inode**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_zget (TYPE_1__*,scalar_t__,int /*<<< orphan*/ **) ; 

int
zfsctl_shares_lookup(struct inode *dip, char *name, struct inode **ipp,
    int flags, cred_t *cr, int *direntflags, pathname_t *realpnp)
{
	zfsvfs_t *zfsvfs = ITOZSB(dip);
	struct inode *ip;
	znode_t *dzp;
	int error;

	ZFS_ENTER(zfsvfs);

	if (zfsvfs->z_shares_dir == 0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(ENOTSUP));
	}

	if ((error = zfs_zget(zfsvfs, zfsvfs->z_shares_dir, &dzp)) == 0) {
		error = zfs_lookup(ZTOI(dzp), name, &ip, 0, cr, NULL, NULL);
		iput(ZTOI(dzp));
	}

	ZFS_EXIT(zfsvfs);

	return (error);
}