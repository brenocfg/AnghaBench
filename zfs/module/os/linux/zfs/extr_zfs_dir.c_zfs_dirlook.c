#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  z_zn_prefetch; int /*<<< orphan*/  z_parent_lock; int /*<<< orphan*/  z_id; int /*<<< orphan*/  z_sa_hdl; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_18__ {int /*<<< orphan*/  z_ctldir; struct TYPE_18__* z_parent; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zfs_dirlock_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct inode {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  pn_bufsize; int /*<<< orphan*/  pn_buf; } ;
typedef  TYPE_3__ pathname_t ;
typedef  int /*<<< orphan*/  parent ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int FIGNORECASE ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SA_ZPL_PARENT (TYPE_2__*) ; 
 int ZCILOOK ; 
 int ZEXISTS ; 
 int /*<<< orphan*/  ZFS_CTLDIR_NAME ; 
 int ZSHARED ; 
 struct inode* ZTOI (TYPE_1__*) ; 
 TYPE_2__* ZTOZSB (TYPE_1__*) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  kcred ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int zfs_dirent_lock (int /*<<< orphan*/ **,TYPE_1__*,char*,TYPE_1__**,int,int*,TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_dirent_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_has_ctldir (TYPE_1__*) ; 
 int zfs_zget (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 struct inode* zfsctl_root (TYPE_1__*) ; 
 int zfsctl_root_lookup (int /*<<< orphan*/ ,char*,struct inode**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
zfs_dirlook(znode_t *dzp, char *name, struct inode **ipp, int flags,
    int *deflg, pathname_t *rpnp)
{
	zfs_dirlock_t *dl;
	znode_t *zp;
	int error = 0;
	uint64_t parent;

	if (name[0] == 0 || (name[0] == '.' && name[1] == 0)) {
		*ipp = ZTOI(dzp);
		igrab(*ipp);
	} else if (name[0] == '.' && name[1] == '.' && name[2] == 0) {
		zfsvfs_t *zfsvfs = ZTOZSB(dzp);

		/*
		 * If we are a snapshot mounted under .zfs, return
		 * the inode pointer for the snapshot directory.
		 */
		if ((error = sa_lookup(dzp->z_sa_hdl,
		    SA_ZPL_PARENT(zfsvfs), &parent, sizeof (parent))) != 0)
			return (error);

		if (parent == dzp->z_id && zfsvfs->z_parent != zfsvfs) {
			error = zfsctl_root_lookup(zfsvfs->z_parent->z_ctldir,
			    "snapshot", ipp, 0, kcred, NULL, NULL);
			return (error);
		}
		rw_enter(&dzp->z_parent_lock, RW_READER);
		error = zfs_zget(zfsvfs, parent, &zp);
		if (error == 0)
			*ipp = ZTOI(zp);
		rw_exit(&dzp->z_parent_lock);
	} else if (zfs_has_ctldir(dzp) && strcmp(name, ZFS_CTLDIR_NAME) == 0) {
		*ipp = zfsctl_root(dzp);
	} else {
		int zf;

		zf = ZEXISTS | ZSHARED;
		if (flags & FIGNORECASE)
			zf |= ZCILOOK;

		error = zfs_dirent_lock(&dl, dzp, name, &zp, zf, deflg, rpnp);
		if (error == 0) {
			*ipp = ZTOI(zp);
			zfs_dirent_unlock(dl);
			dzp->z_zn_prefetch = B_TRUE; /* enable prefetching */
		}
		rpnp = NULL;
	}

	if ((flags & FIGNORECASE) && rpnp && !error)
		(void) strlcpy(rpnp->pn_buf, name, rpnp->pn_bufsize);

	return (error);
}