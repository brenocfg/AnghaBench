#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_type_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_2__ {char* proto; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ update_cookie_t ;
typedef  int /*<<< orphan*/  shareopts ;
typedef  int /*<<< orphan*/  mountpoint ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ZFS_MAXPROPLEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_SHARENFS ; 
 int /*<<< orphan*/  ZFS_PROP_SHARESMB ; 
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  process_share (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_is_mounted (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
update_zfs_shares_cb(zfs_handle_t *zhp, void *pcookie)
{
	update_cookie_t *udata = (update_cookie_t *)pcookie;
	char mountpoint[ZFS_MAXPROPLEN];
	char shareopts[ZFS_MAXPROPLEN];
	char *dataset;
	zfs_type_t type = zfs_get_type(zhp);

	if (type == ZFS_TYPE_FILESYSTEM &&
	    zfs_iter_filesystems(zhp, update_zfs_shares_cb, pcookie) != 0) {
		zfs_close(zhp);
		return (1);
	}

	if (type != ZFS_TYPE_FILESYSTEM) {
		zfs_close(zhp);
		return (0);
	}

	if (zfs_prop_get(zhp, ZFS_PROP_MOUNTPOINT, mountpoint,
	    sizeof (mountpoint), NULL, NULL, 0, B_FALSE) != 0) {
		zfs_close(zhp);
		return (0);
	}

	dataset = (char *)zfs_get_name(zhp);

	if (dataset == NULL) {
		zfs_close(zhp);
		return (0);
	}

	if (!zfs_is_mounted(zhp, NULL)) {
		zfs_close(zhp);
		return (0);
	}

	if ((udata->proto == NULL || strcmp(udata->proto, "nfs") == 0) &&
	    zfs_prop_get(zhp, ZFS_PROP_SHARENFS, shareopts,
	    sizeof (shareopts), NULL, NULL, 0, B_FALSE) == 0 &&
	    strcmp(shareopts, "off") != 0) {
		(void) process_share(udata->handle, NULL, mountpoint, NULL,
		    "nfs", shareopts, NULL, dataset, B_FALSE);
	}

	if ((udata->proto == NULL || strcmp(udata->proto, "smb") == 0) &&
	    zfs_prop_get(zhp, ZFS_PROP_SHARESMB, shareopts,
	    sizeof (shareopts), NULL, NULL, 0, B_FALSE) == 0 &&
	    strcmp(shareopts, "off") != 0) {
		(void) process_share(udata->handle, NULL, mountpoint, NULL,
		    "smb", shareopts, NULL, dataset, B_FALSE);
	}

	zfs_close(zhp);

	return (0);
}