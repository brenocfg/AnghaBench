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
struct TYPE_5__ {int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  offset_t ;
struct TYPE_6__ {int /*<<< orphan*/  f_offset; int /*<<< orphan*/  f_vnode; } ;
typedef  TYPE_2__ file_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VOP_SEEK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmu_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* getf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releasef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_diff(zfs_cmd_t *zc)
{
	file_t *fp;
	offset_t off;
	int error;

	fp = getf(zc->zc_cookie);
	if (fp == NULL)
		return (SET_ERROR(EBADF));

	off = fp->f_offset;

	error = dmu_diff(zc->zc_name, zc->zc_value, fp->f_vnode, &off);

	if (VOP_SEEK(fp->f_vnode, fp->f_offset, &off, NULL) == 0)
		fp->f_offset = off;
	releasef(zc->zc_cookie);

	return (error);
}