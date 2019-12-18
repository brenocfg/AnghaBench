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
struct TYPE_6__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  pathname_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 TYPE_1__* ITOZSB (struct inode*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZFSCTL_INO_SNAPDIRS ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_1__*) ; 
 int dmu_snapshot_lookup (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  simple_dir_inode_operations ; 
 int /*<<< orphan*/  simple_dir_operations ; 
 struct inode* zfsctl_inode_lookup (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
zfsctl_snapdir_lookup(struct inode *dip, char *name, struct inode **ipp,
    int flags, cred_t *cr, int *direntflags, pathname_t *realpnp)
{
	zfsvfs_t *zfsvfs = ITOZSB(dip);
	uint64_t id;
	int error;

	ZFS_ENTER(zfsvfs);

	error = dmu_snapshot_lookup(zfsvfs->z_os, name, &id);
	if (error) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	*ipp = zfsctl_inode_lookup(zfsvfs, ZFSCTL_INO_SNAPDIRS - id,
	    &simple_dir_operations, &simple_dir_inode_operations);
	if (*ipp == NULL)
		error = SET_ERROR(ENOENT);

	ZFS_EXIT(zfsvfs);

	return (error);
}