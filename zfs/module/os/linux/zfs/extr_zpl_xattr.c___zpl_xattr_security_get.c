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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  XATTR_SECURITY_PREFIX ; 
 char* kmem_asprintf (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int zpl_xattr_get (struct inode*,char*,void*,size_t) ; 

__attribute__((used)) static int
__zpl_xattr_security_get(struct inode *ip, const char *name,
    void *value, size_t size)
{
	char *xattr_name;
	int error;
	/* xattr_resolve_name will do this for us if this is defined */
#ifndef HAVE_XATTR_HANDLER_NAME
	if (strcmp(name, "") == 0)
		return (-EINVAL);
#endif
	xattr_name = kmem_asprintf("%s%s", XATTR_SECURITY_PREFIX, name);
	error = zpl_xattr_get(ip, xattr_name, value, size);
	kmem_strfree(xattr_name);

	return (error);
}