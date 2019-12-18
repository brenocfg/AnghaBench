#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  zfs_dirlock_t ;
struct TYPE_3__ {int va_mask; int va_mode; int /*<<< orphan*/ * va_dentry; int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; } ;
typedef  TYPE_1__ vattr_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int CREATE_XATTR_DIR ; 
 int /*<<< orphan*/  ENOENT ; 
 int ERESTART ; 
 int /*<<< orphan*/  EROFS ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int S_IFDIR ; 
 int S_ISVTX ; 
 struct inode* ZTOI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ZTOZSB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZXATTR ; 
 int zfs_dirent_lock (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dirent_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_fuid_map_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_is_readonly (int /*<<< orphan*/ *) ; 
 int zfs_make_xattrdir (int /*<<< orphan*/ *,TYPE_1__*,struct inode**,int /*<<< orphan*/ *) ; 

int
zfs_get_xattrdir(znode_t *zp, struct inode **xipp, cred_t *cr, int flags)
{
	zfsvfs_t	*zfsvfs = ZTOZSB(zp);
	znode_t		*xzp;
	zfs_dirlock_t	*dl;
	vattr_t		va;
	int		error;
top:
	error = zfs_dirent_lock(&dl, zp, "", &xzp, ZXATTR, NULL, NULL);
	if (error)
		return (error);

	if (xzp != NULL) {
		*xipp = ZTOI(xzp);
		zfs_dirent_unlock(dl);
		return (0);
	}

	if (!(flags & CREATE_XATTR_DIR)) {
		zfs_dirent_unlock(dl);
		return (SET_ERROR(ENOENT));
	}

	if (zfs_is_readonly(zfsvfs)) {
		zfs_dirent_unlock(dl);
		return (SET_ERROR(EROFS));
	}

	/*
	 * The ability to 'create' files in an attribute
	 * directory comes from the write_xattr permission on the base file.
	 *
	 * The ability to 'search' an attribute directory requires
	 * read_xattr permission on the base file.
	 *
	 * Once in a directory the ability to read/write attributes
	 * is controlled by the permissions on the attribute file.
	 */
	va.va_mask = ATTR_MODE | ATTR_UID | ATTR_GID;
	va.va_mode = S_IFDIR | S_ISVTX | 0777;
	zfs_fuid_map_ids(zp, cr, &va.va_uid, &va.va_gid);

	va.va_dentry = NULL;
	error = zfs_make_xattrdir(zp, &va, xipp, cr);
	zfs_dirent_unlock(dl);

	if (error == ERESTART) {
		/* NB: we already did dmu_tx_wait() if necessary */
		goto top;
	}

	return (error);
}