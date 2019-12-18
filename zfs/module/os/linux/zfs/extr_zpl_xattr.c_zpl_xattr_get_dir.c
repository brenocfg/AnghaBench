#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  LOOKUP_XATTR ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int zfs_lookup (struct inode*,char*,struct inode**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpl_read_common (struct inode*,void*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zpl_xattr_get_dir(struct inode *ip, const char *name, void *value,
    size_t size, cred_t *cr)
{
	struct inode *dxip = NULL;
	struct inode *xip = NULL;
	loff_t pos = 0;
	int error;

	/* Lookup the xattr directory */
	error = -zfs_lookup(ip, NULL, &dxip, LOOKUP_XATTR, cr, NULL, NULL);
	if (error)
		goto out;

	/* Lookup a specific xattr name in the directory */
	error = -zfs_lookup(dxip, (char *)name, &xip, 0, cr, NULL, NULL);
	if (error)
		goto out;

	if (!size) {
		error = i_size_read(xip);
		goto out;
	}

	if (size < i_size_read(xip)) {
		error = -ERANGE;
		goto out;
	}

	error = zpl_read_common(xip, value, size, &pos, UIO_SYSSPACE, 0, cr);
out:
	if (xip)
		iput(xip);

	if (dxip)
		iput(dxip);

	return (error);
}