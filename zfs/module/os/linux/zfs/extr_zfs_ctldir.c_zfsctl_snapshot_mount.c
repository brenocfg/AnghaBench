#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_5__* z_os; struct TYPE_11__* z_parent; TYPE_1__* z_vfs; } ;
typedef  TYPE_3__ zfsvfs_t ;
typedef  int /*<<< orphan*/  zfs_snapentry_t ;
struct path {TYPE_2__* mnt; struct dentry* dentry; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_12__ {int /*<<< orphan*/  os_spa; } ;
struct TYPE_10__ {int /*<<< orphan*/  mnt_flags; } ;
struct TYPE_9__ {char* vfs_mntpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  EISDIR ; 
 TYPE_3__* ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  MNT_SHRINKABLE ; 
 int MOUNT_BUSY ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMH_WAIT_PROC ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 int call_usermodehelper (char*,char**,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_id (TYPE_5__*) ; 
 char* dname (struct dentry*) ; 
 int /*<<< orphan*/  dprintf (char*,char*,char*) ; 
 scalar_t__ follow_down_one (struct path*) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 char* kmem_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_expire_snapshot ; 
 int /*<<< orphan*/  zfs_snapshot_lock ; 
 int /*<<< orphan*/  zfsctl_snapshot_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfsctl_snapshot_alloc (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*) ; 
 scalar_t__ zfsctl_snapshot_ismounted (char*) ; 
 int zfsctl_snapshot_name (TYPE_3__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfsctl_snapshot_unmount_delay_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zfsctl_snapshot_mount(struct path *path, int flags)
{
	struct dentry *dentry = path->dentry;
	struct inode *ip = dentry->d_inode;
	zfsvfs_t *zfsvfs;
	zfsvfs_t *snap_zfsvfs;
	zfs_snapentry_t *se;
	char *full_name, *full_path;
	char *argv[] = { "/usr/bin/env", "mount", "-t", "zfs", "-n", NULL, NULL,
	    NULL };
	char *envp[] = { NULL };
	int error;
	struct path spath;

	if (ip == NULL)
		return (SET_ERROR(EISDIR));

	zfsvfs = ITOZSB(ip);
	ZFS_ENTER(zfsvfs);

	full_name = kmem_zalloc(ZFS_MAX_DATASET_NAME_LEN, KM_SLEEP);
	full_path = kmem_zalloc(MAXPATHLEN, KM_SLEEP);

	error = zfsctl_snapshot_name(zfsvfs, dname(dentry),
	    ZFS_MAX_DATASET_NAME_LEN, full_name);
	if (error)
		goto error;

	/*
	 * Construct a mount point path from sb of the ctldir inode and dirent
	 * name, instead of from d_path(), so that chroot'd process doesn't fail
	 * on mount.zfs(8).
	 */
	snprintf(full_path, MAXPATHLEN, "%s/.zfs/snapshot/%s",
	    zfsvfs->z_vfs->vfs_mntpoint ? zfsvfs->z_vfs->vfs_mntpoint : "",
	    dname(dentry));

	/*
	 * Multiple concurrent automounts of a snapshot are never allowed.
	 * The snapshot may be manually mounted as many times as desired.
	 */
	if (zfsctl_snapshot_ismounted(full_name)) {
		error = 0;
		goto error;
	}

	/*
	 * Attempt to mount the snapshot from user space.  Normally this
	 * would be done using the vfs_kern_mount() function, however that
	 * function is marked GPL-only and cannot be used.  On error we
	 * careful to log the real error to the console and return EISDIR
	 * to safely abort the automount.  This should be very rare.
	 *
	 * If the user mode helper happens to return EBUSY, a concurrent
	 * mount is already in progress in which case the error is ignored.
	 * Take note that if the program was executed successfully the return
	 * value from call_usermodehelper() will be (exitcode << 8 + signal).
	 */
	dprintf("mount; name=%s path=%s\n", full_name, full_path);
	argv[5] = full_name;
	argv[6] = full_path;
	error = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC);
	if (error) {
		if (!(error & MOUNT_BUSY << 8)) {
			zfs_dbgmsg("Unable to automount %s error=%d",
			    full_path, error);
			error = SET_ERROR(EISDIR);
		} else {
			/*
			 * EBUSY, this could mean a concurrent mount, or the
			 * snapshot has already been mounted at completely
			 * different place. We return 0 so VFS will retry. For
			 * the latter case the VFS will retry several times
			 * and return ELOOP, which is probably not a very good
			 * behavior.
			 */
			error = 0;
		}
		goto error;
	}

	/*
	 * Follow down in to the mounted snapshot and set MNT_SHRINKABLE
	 * to identify this as an automounted filesystem.
	 */
	spath = *path;
	path_get(&spath);
	if (follow_down_one(&spath)) {
		snap_zfsvfs = ITOZSB(spath.dentry->d_inode);
		snap_zfsvfs->z_parent = zfsvfs;
		dentry = spath.dentry;
		spath.mnt->mnt_flags |= MNT_SHRINKABLE;

		rw_enter(&zfs_snapshot_lock, RW_WRITER);
		se = zfsctl_snapshot_alloc(full_name, full_path,
		    snap_zfsvfs->z_os->os_spa, dmu_objset_id(snap_zfsvfs->z_os),
		    dentry);
		zfsctl_snapshot_add(se);
		zfsctl_snapshot_unmount_delay_impl(se, zfs_expire_snapshot);
		rw_exit(&zfs_snapshot_lock);
	}
	path_put(&spath);
error:
	kmem_free(full_name, ZFS_MAX_DATASET_NAME_LEN);
	kmem_free(full_path, MAXPATHLEN);

	ZFS_EXIT(zfsvfs);

	return (error);
}