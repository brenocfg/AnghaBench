#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zfs_type; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ ZFS_TYPE_BOOKMARK ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int lzc_destroy (int /*<<< orphan*/ ) ; 
 int lzc_destroy_bookmarks (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lzc_destroy_snaps (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_mountpoint (TYPE_1__*) ; 
 int zfs_standard_error_fmt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_destroy(zfs_handle_t *zhp, boolean_t defer)
{
	int error;

	if (zhp->zfs_type != ZFS_TYPE_SNAPSHOT && defer)
		return (EINVAL);

	if (zhp->zfs_type == ZFS_TYPE_BOOKMARK) {
		nvlist_t *nv = fnvlist_alloc();
		fnvlist_add_boolean(nv, zhp->zfs_name);
		error = lzc_destroy_bookmarks(nv, NULL);
		fnvlist_free(nv);
		if (error != 0) {
			return (zfs_standard_error_fmt(zhp->zfs_hdl, error,
			    dgettext(TEXT_DOMAIN, "cannot destroy '%s'"),
			    zhp->zfs_name));
		}
		return (0);
	}

	if (zhp->zfs_type == ZFS_TYPE_SNAPSHOT) {
		nvlist_t *nv = fnvlist_alloc();
		fnvlist_add_boolean(nv, zhp->zfs_name);
		error = lzc_destroy_snaps(nv, defer, NULL);
		fnvlist_free(nv);
	} else {
		error = lzc_destroy(zhp->zfs_name);
	}

	if (error != 0 && error != ENOENT) {
		return (zfs_standard_error_fmt(zhp->zfs_hdl, errno,
		    dgettext(TEXT_DOMAIN, "cannot destroy '%s'"),
		    zhp->zfs_name));
	}

	remove_mountpoint(zhp);

	return (0);
}