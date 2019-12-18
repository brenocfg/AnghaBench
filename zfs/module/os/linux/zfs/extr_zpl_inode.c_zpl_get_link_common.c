#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int uio_iovcnt; void* uio_resid; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  TYPE_2__ uio_t ;
struct iovec {char* iov_base; void* iov_len; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CRED () ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 void* MAXPATHLEN ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (char*,void*) ; 
 char* kmem_zalloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int zfs_readlink (struct inode*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zpl_get_link_common(struct dentry *dentry, struct inode *ip, char **link)
{
	fstrans_cookie_t cookie;
	cred_t *cr = CRED();
	struct iovec iov;
	uio_t uio = { { 0 }, 0 };
	int error;

	crhold(cr);
	*link = NULL;
	iov.iov_len = MAXPATHLEN;
	iov.iov_base = kmem_zalloc(MAXPATHLEN, KM_SLEEP);

	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_resid = (MAXPATHLEN - 1);

	cookie = spl_fstrans_mark();
	error = -zfs_readlink(ip, &uio, cr);
	spl_fstrans_unmark(cookie);
	crfree(cr);

	if (error)
		kmem_free(iov.iov_base, MAXPATHLEN);
	else
		*link = iov.iov_base;

	return (error);
}