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
struct _buf {int /*<<< orphan*/ * vp; } ;
typedef  struct _buf _buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  kfree (struct _buf*) ; 
 struct _buf* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_flags_convert (int /*<<< orphan*/ ) ; 
 int vn_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct _buf *
kobj_open_file(const char *name)
{
	struct _buf *file;
	vnode_t *vp;
	int rc;

	file = kmalloc(sizeof (_buf_t), kmem_flags_convert(KM_SLEEP));
	if (file == NULL)
		return ((_buf_t *)-1UL);

	if ((rc = vn_open(name, UIO_SYSSPACE, FREAD, 0644, &vp, 0, 0))) {
		kfree(file);
		return ((_buf_t *)-1UL);
	}

	file->vp = vp;

	return (file);
}