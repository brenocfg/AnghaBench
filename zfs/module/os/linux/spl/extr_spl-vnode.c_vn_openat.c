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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uio_seg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_flags_convert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rootdir ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 
 int vn_open (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **,int,void*) ; 

int
vn_openat(const char *path, uio_seg_t seg, int flags, int mode,
    vnode_t **vpp, int x1, void *x2, vnode_t *vp, int fd)
{
	char *realpath;
	int len, rc;

	ASSERT(vp == rootdir);

	len = strlen(path) + 2;
	realpath = kmalloc(len, kmem_flags_convert(KM_SLEEP));
	if (!realpath)
		return (ENOMEM);

	(void) snprintf(realpath, len, "/%s", path);
	rc = vn_open(realpath, seg, flags, mode, vpp, x1, x2);
	kfree(realpath);

	return (rc);
}