#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int z_pflags; int /*<<< orphan*/ * z_sa_hdl; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_14__ {scalar_t__ z_utf8; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct inode {int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  pathname_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_EXECUTE ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int FIGNORECASE ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 TYPE_2__* ITOZSB (struct inode*) ; 
 int LOOKUP_XATTR ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U8_VALIDATE_ENTIRE ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int ZFS_XATTR ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ u8_validate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int zfs_dirlook (TYPE_1__*,char*,struct inode**,int,int*,int /*<<< orphan*/ *) ; 
 int zfs_fastaccesschk_execute (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_get_xattrdir (TYPE_1__*,struct inode**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_inode_update (TYPE_1__*) ; 
 int zfs_zaccess (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zfs_lookup(struct inode *dip, char *nm, struct inode **ipp, int flags,
    cred_t *cr, int *direntflags, pathname_t *realpnp)
{
	znode_t *zdp = ITOZ(dip);
	zfsvfs_t *zfsvfs = ITOZSB(dip);
	int error = 0;

	/*
	 * Fast path lookup, however we must skip DNLC lookup
	 * for case folding or normalizing lookups because the
	 * DNLC code only stores the passed in name.  This means
	 * creating 'a' and removing 'A' on a case insensitive
	 * file system would work, but DNLC still thinks 'a'
	 * exists and won't let you create it again on the next
	 * pass through fast path.
	 */
	if (!(flags & (LOOKUP_XATTR | FIGNORECASE))) {

		if (!S_ISDIR(dip->i_mode)) {
			return (SET_ERROR(ENOTDIR));
		} else if (zdp->z_sa_hdl == NULL) {
			return (SET_ERROR(EIO));
		}

		if (nm[0] == 0 || (nm[0] == '.' && nm[1] == '\0')) {
			error = zfs_fastaccesschk_execute(zdp, cr);
			if (!error) {
				*ipp = dip;
				igrab(*ipp);
				return (0);
			}
			return (error);
		}
	}

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zdp);

	*ipp = NULL;

	if (flags & LOOKUP_XATTR) {
		/*
		 * We don't allow recursive attributes..
		 * Maybe someday we will.
		 */
		if (zdp->z_pflags & ZFS_XATTR) {
			ZFS_EXIT(zfsvfs);
			return (SET_ERROR(EINVAL));
		}

		if ((error = zfs_get_xattrdir(zdp, ipp, cr, flags))) {
			ZFS_EXIT(zfsvfs);
			return (error);
		}

		/*
		 * Do we have permission to get into attribute directory?
		 */

		if ((error = zfs_zaccess(ITOZ(*ipp), ACE_EXECUTE, 0,
		    B_FALSE, cr))) {
			iput(*ipp);
			*ipp = NULL;
		}

		ZFS_EXIT(zfsvfs);
		return (error);
	}

	if (!S_ISDIR(dip->i_mode)) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(ENOTDIR));
	}

	/*
	 * Check accessibility of directory.
	 */

	if ((error = zfs_zaccess(zdp, ACE_EXECUTE, 0, B_FALSE, cr))) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	if (zfsvfs->z_utf8 && u8_validate(nm, strlen(nm),
	    NULL, U8_VALIDATE_ENTIRE, &error) < 0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EILSEQ));
	}

	error = zfs_dirlook(zdp, nm, ipp, flags, direntflags, realpnp);
	if ((error == 0) && (*ipp))
		zfs_inode_update(ITOZ(*ipp));

	ZFS_EXIT(zfsvfs);
	return (error);
}