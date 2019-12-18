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

/* Variables and functions */
 int /*<<< orphan*/  MNTOPT_ATIME ; 
 int /*<<< orphan*/  MNTOPT_DEVICES ; 
 int /*<<< orphan*/  MNTOPT_EXEC ; 
 int /*<<< orphan*/  MNTOPT_NBMAND ; 
 int /*<<< orphan*/  MNTOPT_NOATIME ; 
 int /*<<< orphan*/  MNTOPT_NODEVICES ; 
 int /*<<< orphan*/  MNTOPT_NOEXEC ; 
 int /*<<< orphan*/  MNTOPT_NONBMAND ; 
 int /*<<< orphan*/  MNTOPT_NOSETUID ; 
 int /*<<< orphan*/  MNTOPT_RELATIME ; 
 int /*<<< orphan*/  MNTOPT_RO ; 
 int /*<<< orphan*/  MNTOPT_RW ; 
 int /*<<< orphan*/  MNTOPT_SETUID ; 
 int /*<<< orphan*/  MNTOPT_STRICTATIME ; 
 int /*<<< orphan*/  ZFS_PROP_ATIME ; 
 int /*<<< orphan*/  ZFS_PROP_DEVICES ; 
 int /*<<< orphan*/  ZFS_PROP_EXEC ; 
 int /*<<< orphan*/  ZFS_PROP_NBMAND ; 
 int /*<<< orphan*/  ZFS_PROP_READONLY ; 
 int /*<<< orphan*/  ZFS_PROP_RELATIME ; 
 int /*<<< orphan*/  ZFS_PROP_SETUID ; 
 int /*<<< orphan*/ * strstr (char*,int /*<<< orphan*/ ) ; 
 int zfs_add_option (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_add_options(zfs_handle_t *zhp, char *options, int len)
{
	int error = 0;

	error = zfs_add_option(zhp, options, len,
	    ZFS_PROP_ATIME, MNTOPT_ATIME, MNTOPT_NOATIME);
	/*
	 * don't add relatime/strictatime when atime=off, otherwise strictatime
	 * will force atime=on
	 */
	if (strstr(options, MNTOPT_NOATIME) == NULL) {
		error = zfs_add_option(zhp, options, len,
		    ZFS_PROP_RELATIME, MNTOPT_RELATIME, MNTOPT_STRICTATIME);
	}
	error = error ? error : zfs_add_option(zhp, options, len,
	    ZFS_PROP_DEVICES, MNTOPT_DEVICES, MNTOPT_NODEVICES);
	error = error ? error : zfs_add_option(zhp, options, len,
	    ZFS_PROP_EXEC, MNTOPT_EXEC, MNTOPT_NOEXEC);
	error = error ? error : zfs_add_option(zhp, options, len,
	    ZFS_PROP_READONLY, MNTOPT_RO, MNTOPT_RW);
	error = error ? error : zfs_add_option(zhp, options, len,
	    ZFS_PROP_SETUID, MNTOPT_SETUID, MNTOPT_NOSETUID);
	error = error ? error : zfs_add_option(zhp, options, len,
	    ZFS_PROP_NBMAND, MNTOPT_NBMAND, MNTOPT_NONBMAND);

	return (error);
}