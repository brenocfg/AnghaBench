#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  z_xattr_lock; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CRED () ; 
 TYPE_1__* ITOZ (struct inode*) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  ZPL_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZPL_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZPL_VERIFY_ZP (TYPE_1__*) ; 
 int /*<<< orphan*/ * ZTOZSB (TYPE_1__*) ; 
 int __zpl_xattr_get (struct inode*,char const*,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zpl_xattr_get(struct inode *ip, const char *name, void *value, size_t size)
{
	znode_t *zp = ITOZ(ip);
	zfsvfs_t *zfsvfs = ZTOZSB(zp);
	cred_t *cr = CRED();
	fstrans_cookie_t cookie;
	int error;

	crhold(cr);
	cookie = spl_fstrans_mark();
	ZPL_ENTER(zfsvfs);
	ZPL_VERIFY_ZP(zp);
	rw_enter(&zp->z_xattr_lock, RW_READER);
	error = __zpl_xattr_get(ip, name, value, size, cr);
	rw_exit(&zp->z_xattr_lock);
	ZPL_EXIT(zfsvfs);
	spl_fstrans_unmark(cookie);
	crfree(cr);

	return (error);
}