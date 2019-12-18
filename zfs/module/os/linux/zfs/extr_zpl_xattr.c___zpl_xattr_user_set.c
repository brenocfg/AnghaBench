#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_2__ {int z_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 TYPE_1__* ITOZSB (struct inode*) ; 
 int /*<<< orphan*/  XATTR_USER_PREFIX ; 
 int ZSB_XATTR ; 
 char* kmem_asprintf (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int zpl_xattr_set (struct inode*,char*,void const*,size_t,int) ; 

__attribute__((used)) static int
__zpl_xattr_user_set(struct inode *ip, const char *name,
    const void *value, size_t size, int flags)
{
	char *xattr_name;
	int error;
	/* xattr_resolve_name will do this for us if this is defined */
#ifndef HAVE_XATTR_HANDLER_NAME
	if (strcmp(name, "") == 0)
		return (-EINVAL);
#endif
	if (!(ITOZSB(ip)->z_flags & ZSB_XATTR))
		return (-EOPNOTSUPP);

	xattr_name = kmem_asprintf("%s%s", XATTR_USER_PREFIX, name);
	error = zpl_xattr_set(ip, xattr_name, value, size, flags);
	kmem_strfree(xattr_name);

	return (error);
}