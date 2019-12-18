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
struct TYPE_6__ {scalar_t__ z_case; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EACCES ; 
 int ENOENT ; 
 int ENOTSUP ; 
 TYPE_1__* ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MNT_FORCE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZFS_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int dmu_snapshot_realname (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsl_destroy_snapshot (char*,int /*<<< orphan*/ ) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_admin_snapshot ; 
 int zfs_secpolicy_destroy_perms (char*,int /*<<< orphan*/ *) ; 
 int zfsctl_snapshot_name (TYPE_1__*,char*,int /*<<< orphan*/ ,char*) ; 
 int zfsctl_snapshot_unmount (char*,int /*<<< orphan*/ ) ; 

int
zfsctl_snapdir_remove(struct inode *dip, char *name, cred_t *cr, int flags)
{
	zfsvfs_t *zfsvfs = ITOZSB(dip);
	char *snapname, *real;
	int error;

	if (!zfs_admin_snapshot)
		return (SET_ERROR(EACCES));

	ZFS_ENTER(zfsvfs);

	snapname = kmem_alloc(ZFS_MAX_DATASET_NAME_LEN, KM_SLEEP);
	real = kmem_alloc(ZFS_MAX_DATASET_NAME_LEN, KM_SLEEP);

	if (zfsvfs->z_case == ZFS_CASE_INSENSITIVE) {
		error = dmu_snapshot_realname(zfsvfs->z_os, name, real,
		    ZFS_MAX_DATASET_NAME_LEN, NULL);
		if (error == 0) {
			name = real;
		} else if (error != ENOTSUP) {
			goto out;
		}
	}

	error = zfsctl_snapshot_name(ITOZSB(dip), name,
	    ZFS_MAX_DATASET_NAME_LEN, snapname);
	if (error == 0)
		error = zfs_secpolicy_destroy_perms(snapname, cr);
	if (error != 0)
		goto out;

	error = zfsctl_snapshot_unmount(snapname, MNT_FORCE);
	if ((error == 0) || (error == ENOENT))
		error = dsl_destroy_snapshot(snapname, B_FALSE);
out:
	kmem_free(snapname, ZFS_MAX_DATASET_NAME_LEN);
	kmem_free(real, ZFS_MAX_DATASET_NAME_LEN);

	ZFS_EXIT(zfsvfs);

	return (error);
}