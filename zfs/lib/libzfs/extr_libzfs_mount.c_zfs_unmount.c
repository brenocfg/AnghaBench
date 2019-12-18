#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct mnttab {char const* mnt_mountp; } ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int MS_CRYPT ; 
 scalar_t__ ZFS_KEYSTATUS_AVAILABLE ; 
 int /*<<< orphan*/  ZFS_PROP_ENCRYPTION ; 
 int /*<<< orphan*/  ZFS_PROP_KEYSTATUS ; 
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ ZIO_CRYPT_OFF ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ libzfs_mnttab_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mnttab*) ; 
 int /*<<< orphan*/  libzfs_mnttab_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  share_all_proto ; 
 scalar_t__ unmount_one (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ zfs_crypto_get_encryption_root (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_crypto_unload_key (TYPE_1__*) ; 
 scalar_t__ zfs_get_type (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_mount (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refresh_properties (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_shareall (TYPE_1__*) ; 
 char* zfs_strdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ zfs_unshare_proto (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

int
zfs_unmount(zfs_handle_t *zhp, const char *mountpoint, int flags)
{
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	struct mnttab entry;
	char *mntpt = NULL;
	boolean_t encroot, unmounted = B_FALSE;

	/* check to see if we need to unmount the filesystem */
	if (mountpoint != NULL || ((zfs_get_type(zhp) == ZFS_TYPE_FILESYSTEM) &&
	    libzfs_mnttab_find(hdl, zhp->zfs_name, &entry) == 0)) {
		/*
		 * mountpoint may have come from a call to
		 * getmnt/getmntany if it isn't NULL. If it is NULL,
		 * we know it comes from libzfs_mnttab_find which can
		 * then get freed later. We strdup it to play it safe.
		 */
		if (mountpoint == NULL)
			mntpt = zfs_strdup(hdl, entry.mnt_mountp);
		else
			mntpt = zfs_strdup(hdl, mountpoint);

		/*
		 * Unshare and unmount the filesystem
		 */
		if (zfs_unshare_proto(zhp, mntpt, share_all_proto) != 0) {
			free(mntpt);
			return (-1);
		}

		if (unmount_one(hdl, mntpt, flags) != 0) {
			free(mntpt);
			(void) zfs_shareall(zhp);
			return (-1);
		}

		libzfs_mnttab_remove(hdl, zhp->zfs_name);
		free(mntpt);
		unmounted = B_TRUE;
	}

	/*
	 * If the MS_CRYPT flag is provided we must ensure we attempt to
	 * unload the dataset's key regardless of whether we did any work
	 * to unmount it. We only do this for encryption roots.
	 */
	if ((flags & MS_CRYPT) != 0 &&
	    zfs_prop_get_int(zhp, ZFS_PROP_ENCRYPTION) != ZIO_CRYPT_OFF) {
		zfs_refresh_properties(zhp);

		if (zfs_crypto_get_encryption_root(zhp, &encroot, NULL) != 0 &&
		    unmounted) {
			(void) zfs_mount(zhp, NULL, 0);
			return (-1);
		}

		if (encroot && zfs_prop_get_int(zhp, ZFS_PROP_KEYSTATUS) ==
		    ZFS_KEYSTATUS_AVAILABLE &&
		    zfs_crypto_unload_key(zhp) != 0) {
			(void) zfs_mount(zhp, NULL, 0);
			return (-1);
		}
	}

	return (0);
}