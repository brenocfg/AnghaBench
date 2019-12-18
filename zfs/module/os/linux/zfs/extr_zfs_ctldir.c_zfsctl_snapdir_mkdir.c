#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  vattr_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EILSEQ ; 
 TYPE_1__* ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  dmu_objset_name (int /*<<< orphan*/ ,char*) ; 
 int dmu_objset_snapshot_one (char*,char*) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_admin_snapshot ; 
 scalar_t__ zfs_component_namecheck (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_snapshot_perms (char*,int /*<<< orphan*/ *) ; 
 int zfsctl_snapdir_lookup (struct inode*,char*,struct inode**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
zfsctl_snapdir_mkdir(struct inode *dip, char *dirname, vattr_t *vap,
    struct inode **ipp, cred_t *cr, int flags)
{
	zfsvfs_t *zfsvfs = ITOZSB(dip);
	char *dsname;
	int error;

	if (!zfs_admin_snapshot)
		return (SET_ERROR(EACCES));

	dsname = kmem_alloc(ZFS_MAX_DATASET_NAME_LEN, KM_SLEEP);

	if (zfs_component_namecheck(dirname, NULL, NULL) != 0) {
		error = SET_ERROR(EILSEQ);
		goto out;
	}

	dmu_objset_name(zfsvfs->z_os, dsname);

	error = zfs_secpolicy_snapshot_perms(dsname, cr);
	if (error != 0)
		goto out;

	if (error == 0) {
		error = dmu_objset_snapshot_one(dsname, dirname);
		if (error != 0)
			goto out;

		error = zfsctl_snapdir_lookup(dip, dirname, ipp,
		    0, cr, NULL, NULL);
	}
out:
	kmem_free(dsname, ZFS_MAX_DATASET_NAME_LEN);

	return (error);
}