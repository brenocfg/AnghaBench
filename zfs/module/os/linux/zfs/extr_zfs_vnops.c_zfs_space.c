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
typedef  int /*<<< orphan*/  znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  offset_t ;
struct TYPE_4__ {scalar_t__ l_len; scalar_t__ l_start; } ;
typedef  TYPE_1__ flock64_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_WRITE_DATA ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EROFS ; 
 int F_FREESP ; 
 int /*<<< orphan*/ * ITOZ (struct inode*) ; 
 int /*<<< orphan*/ * ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (int /*<<< orphan*/ *) ; 
 int convoff (struct inode*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfs_freesp (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_is_readonly (int /*<<< orphan*/ *) ; 
 int zfs_zaccess (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zfs_space(struct inode *ip, int cmd, flock64_t *bfp, int flag,
    offset_t offset, cred_t *cr)
{
	znode_t		*zp = ITOZ(ip);
	zfsvfs_t	*zfsvfs = ITOZSB(ip);
	uint64_t	off, len;
	int		error;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	if (cmd != F_FREESP) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EINVAL));
	}

	/*
	 * Callers might not be able to detect properly that we are read-only,
	 * so check it explicitly here.
	 */
	if (zfs_is_readonly(zfsvfs)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EROFS));
	}

	if ((error = convoff(ip, bfp, SEEK_SET, offset))) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	if (bfp->l_len < 0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EINVAL));
	}

	/*
	 * Permissions aren't checked on Solaris because on this OS
	 * zfs_space() can only be called with an opened file handle.
	 * On Linux we can get here through truncate_range() which
	 * operates directly on inodes, so we need to check access rights.
	 */
	if ((error = zfs_zaccess(zp, ACE_WRITE_DATA, 0, B_FALSE, cr))) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	off = bfp->l_start;
	len = bfp->l_len; /* 0 means from off to end of file */

	error = zfs_freesp(zp, off, len, flag, TRUE);

	ZFS_EXIT(zfsvfs);
	return (error);
}