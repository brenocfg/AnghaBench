#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  z_xattr_lock; scalar_t__ z_is_sa; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_13__ {scalar_t__ z_use_sa; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_14__ {size_t member_0; char* member_2; int offset; struct dentry* member_3; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_3__ xattr_filldir_t ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CRED () ; 
 TYPE_1__* ITOZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  ZPL_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZPL_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  ZPL_VERIFY_ZP (TYPE_1__*) ; 
 TYPE_2__* ZTOZSB (TYPE_1__*) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int zpl_xattr_list_dir (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int zpl_xattr_list_sa (TYPE_3__*) ; 

ssize_t
zpl_xattr_list(struct dentry *dentry, char *buffer, size_t buffer_size)
{
	znode_t *zp = ITOZ(dentry->d_inode);
	zfsvfs_t *zfsvfs = ZTOZSB(zp);
	xattr_filldir_t xf = { buffer_size, 0, buffer, dentry };
	cred_t *cr = CRED();
	fstrans_cookie_t cookie;
	int error = 0;

	crhold(cr);
	cookie = spl_fstrans_mark();
	ZPL_ENTER(zfsvfs);
	ZPL_VERIFY_ZP(zp);
	rw_enter(&zp->z_xattr_lock, RW_READER);

	if (zfsvfs->z_use_sa && zp->z_is_sa) {
		error = zpl_xattr_list_sa(&xf);
		if (error)
			goto out;
	}

	error = zpl_xattr_list_dir(&xf, cr);
	if (error)
		goto out;

	error = xf.offset;
out:

	rw_exit(&zp->z_xattr_lock);
	ZPL_EXIT(zfsvfs);
	spl_fstrans_unmark(cookie);
	crfree(cr);

	return (error);
}