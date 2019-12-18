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
struct _buf {int /*<<< orphan*/  vp; } ;
typedef  unsigned int ssize_t ;
typedef  int /*<<< orphan*/  offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 scalar_t__ vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int
kobj_read_file(struct _buf *file, char *buf, unsigned size, unsigned off)
{
	ssize_t resid;

	if (vn_rdwr(UIO_READ, file->vp, buf, size, (offset_t)off,
	    UIO_SYSSPACE, 0, 0, 0, &resid) != 0)
		return (-1);

	return (size - resid);
}