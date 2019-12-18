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
struct xattr {int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; int /*<<< orphan*/ * name; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int __zpl_xattr_security_set (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zpl_xattr_security_init_impl(struct inode *ip, const struct xattr *xattrs,
    void *fs_info)
{
	const struct xattr *xattr;
	int error = 0;

	for (xattr = xattrs; xattr->name != NULL; xattr++) {
		error = __zpl_xattr_security_set(ip,
		    xattr->name, xattr->value, xattr->value_len, 0);

		if (error < 0)
			break;
	}

	return (error);
}