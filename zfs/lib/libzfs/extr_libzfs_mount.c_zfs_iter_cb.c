#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  get_all_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ ZFS_CANMOUNT_NOAUTO ; 
 scalar_t__ ZFS_KEYSTATUS_UNAVAILABLE ; 
 int /*<<< orphan*/  ZFS_PROP_CANMOUNT ; 
 int /*<<< orphan*/  ZFS_PROP_INCONSISTENT ; 
 int /*<<< orphan*/  ZFS_PROP_KEYSTATUS ; 
 int /*<<< orphan*/  ZFS_PROP_RECEIVE_RESUME_TOKEN ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  libzfs_add_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_iter_cb(zfs_handle_t *zhp, void *data)
{
	get_all_cb_t *cbp = data;

	if (!(zfs_get_type(zhp) & ZFS_TYPE_FILESYSTEM)) {
		zfs_close(zhp);
		return (0);
	}

	if (zfs_prop_get_int(zhp, ZFS_PROP_CANMOUNT) == ZFS_CANMOUNT_NOAUTO) {
		zfs_close(zhp);
		return (0);
	}

	if (zfs_prop_get_int(zhp, ZFS_PROP_KEYSTATUS) ==
	    ZFS_KEYSTATUS_UNAVAILABLE) {
		zfs_close(zhp);
		return (0);
	}

	/*
	 * If this filesystem is inconsistent and has a receive resume
	 * token, we can not mount it.
	 */
	if (zfs_prop_get_int(zhp, ZFS_PROP_INCONSISTENT) &&
	    zfs_prop_get(zhp, ZFS_PROP_RECEIVE_RESUME_TOKEN,
	    NULL, 0, NULL, NULL, 0, B_TRUE) == 0) {
		zfs_close(zhp);
		return (0);
	}

	libzfs_add_handle(cbp, zhp);
	if (zfs_iter_filesystems(zhp, zfs_iter_cb, cbp) != 0) {
		zfs_close(zhp);
		return (-1);
	}
	return (0);
}