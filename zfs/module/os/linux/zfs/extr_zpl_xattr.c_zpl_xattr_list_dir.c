#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* dentry; } ;
typedef  TYPE_2__ xattr_filldir_t ;
struct inode {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  LOOKUP_XATTR ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int zfs_lookup (struct inode*,int /*<<< orphan*/ *,struct inode**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpl_xattr_readdir (struct inode*,TYPE_2__*) ; 

__attribute__((used)) static ssize_t
zpl_xattr_list_dir(xattr_filldir_t *xf, cred_t *cr)
{
	struct inode *ip = xf->dentry->d_inode;
	struct inode *dxip = NULL;
	int error;

	/* Lookup the xattr directory */
	error = -zfs_lookup(ip, NULL, &dxip, LOOKUP_XATTR, cr, NULL, NULL);
	if (error) {
		if (error == -ENOENT)
			error = 0;

		return (error);
	}

	error = zpl_xattr_readdir(dxip, xf);
	iput(dxip);

	return (error);
}