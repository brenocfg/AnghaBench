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
 int /*<<< orphan*/  ZFS_PROP_VERSION ; 
 int ZPL_VERSION ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_unsupp_fs(zfs_handle_t *zhp, void *unsupp_fs)
{
	int zfs_version = (int)zfs_prop_get_int(zhp, ZFS_PROP_VERSION);
	int *count = (int *)unsupp_fs;

	if (zfs_version > ZPL_VERSION) {
		(void) printf(gettext("%s (v%d) is not supported by this "
		    "implementation of ZFS.\n"),
		    zfs_get_name(zhp), zfs_version);
		(*count)++;
	}

	zfs_iter_filesystems(zhp, check_unsupp_fs, unsupp_fs);

	zfs_close(zhp);

	return (0);
}