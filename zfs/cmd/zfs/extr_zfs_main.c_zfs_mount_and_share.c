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
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ ZFS_CANMOUNT_ON ; 
 int /*<<< orphan*/  ZFS_PROP_CANMOUNT ; 
 scalar_t__ ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ geteuid () ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_valid_for_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_share (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_mount_and_share(libzfs_handle_t *hdl, const char *dataset, zfs_type_t type)
{
	zfs_handle_t *zhp = NULL;
	int ret = 0;

	zhp = zfs_open(hdl, dataset, type);
	if (zhp == NULL)
		return (1);

	/*
	 * Volumes may neither be mounted or shared.  Potentially in the
	 * future filesystems detected on these volumes could be mounted.
	 */
	if (zfs_get_type(zhp) == ZFS_TYPE_VOLUME) {
		zfs_close(zhp);
		return (0);
	}

	/*
	 * Mount and/or share the new filesystem as appropriate.  We provide a
	 * verbose error message to let the user know that their filesystem was
	 * in fact created, even if we failed to mount or share it.
	 *
	 * If the user doesn't want the dataset automatically mounted, then
	 * skip the mount/share step
	 */
	if (zfs_prop_valid_for_type(ZFS_PROP_CANMOUNT, type, B_FALSE) &&
	    zfs_prop_get_int(zhp, ZFS_PROP_CANMOUNT) == ZFS_CANMOUNT_ON) {
		if (geteuid() != 0) {
			(void) fprintf(stderr, gettext("filesystem "
			    "successfully created, but it may only be "
			    "mounted by root\n"));
			ret = 1;
		} else if (zfs_mount(zhp, NULL, 0) != 0) {
			(void) fprintf(stderr, gettext("filesystem "
			    "successfully created, but not mounted\n"));
			ret = 1;
		} else if (zfs_share(zhp) != 0) {
			(void) fprintf(stderr, gettext("filesystem "
			    "successfully created, but not shared\n"));
			ret = 1;
		}
	}

	zfs_close(zhp);

	return (ret);
}