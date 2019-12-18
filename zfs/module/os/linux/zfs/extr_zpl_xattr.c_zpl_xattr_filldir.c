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
struct TYPE_4__ {char* buf; int offset; int size; } ;
typedef  TYPE_1__ xattr_filldir_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  zpl_xattr_permission (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static int
zpl_xattr_filldir(xattr_filldir_t *xf, const char *name, int name_len)
{
	/* Check permissions using the per-namespace list xattr handler. */
	if (!zpl_xattr_permission(xf, name, name_len))
		return (0);

	/* When xf->buf is NULL only calculate the required size. */
	if (xf->buf) {
		if (xf->offset + name_len + 1 > xf->size)
			return (-ERANGE);

		memcpy(xf->buf + xf->offset, name, name_len);
		xf->buf[xf->offset + name_len] = '\0';
	}

	xf->offset += (name_len + 1);

	return (0);
}