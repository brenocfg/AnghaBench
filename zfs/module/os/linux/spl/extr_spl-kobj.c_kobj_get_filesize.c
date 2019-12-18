#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  va_size; } ;
typedef  TYPE_1__ vattr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct _buf {int /*<<< orphan*/  vp; } ;

/* Variables and functions */
 int VOP_GETATTR (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
kobj_get_filesize(struct _buf *file, uint64_t *size)
{
	vattr_t vap;
	int rc;

	rc = VOP_GETATTR(file->vp, &vap, 0, 0, NULL);
	if (rc)
		return (rc);

	*size = vap.va_size;

	return (rc);
}