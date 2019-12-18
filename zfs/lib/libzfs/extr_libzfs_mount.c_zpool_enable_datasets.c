#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zpool_hdl; int /*<<< orphan*/  zpool_name; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_9__ {char const* ms_mntopts; int ms_mntflags; int ms_mntstatus; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ mount_state_t ;
struct TYPE_10__ {int cb_used; int /*<<< orphan*/ * cb_handles; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ get_all_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libzfs_add_handle (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_foreach_mountpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_iter_cb ; 
 scalar_t__ zfs_iter_filesystems (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_mount_one ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_share_one ; 

int
zpool_enable_datasets(zpool_handle_t *zhp, const char *mntopts, int flags)
{
	get_all_cb_t cb = { 0 };
	mount_state_t ms = { 0 };
	zfs_handle_t *zfsp;
	int ret = 0;

	if ((zfsp = zfs_open(zhp->zpool_hdl, zhp->zpool_name,
	    ZFS_TYPE_DATASET)) == NULL)
		goto out;

	/*
	 * Gather all non-snapshot datasets within the pool. Start by adding
	 * the root filesystem for this pool to the list, and then iterate
	 * over all child filesystems.
	 */
	libzfs_add_handle(&cb, zfsp);
	if (zfs_iter_filesystems(zfsp, zfs_iter_cb, &cb) != 0)
		goto out;

	/*
	 * Mount all filesystems
	 */
	ms.ms_mntopts = mntopts;
	ms.ms_mntflags = flags;
	zfs_foreach_mountpoint(zhp->zpool_hdl, cb.cb_handles, cb.cb_used,
	    zfs_mount_one, &ms, B_TRUE);
	if (ms.ms_mntstatus != 0)
		ret = ms.ms_mntstatus;

	/*
	 * Share all filesystems that need to be shared. This needs to be
	 * a separate pass because libshare is not mt-safe, and so we need
	 * to share serially.
	 */
	ms.ms_mntstatus = 0;
	zfs_foreach_mountpoint(zhp->zpool_hdl, cb.cb_handles, cb.cb_used,
	    zfs_share_one, &ms, B_FALSE);
	if (ms.ms_mntstatus != 0)
		ret = ms.ms_mntstatus;

out:
	for (int i = 0; i < cb.cb_used; i++)
		zfs_close(cb.cb_handles[i]);
	free(cb.cb_handles);

	return (ret);
}