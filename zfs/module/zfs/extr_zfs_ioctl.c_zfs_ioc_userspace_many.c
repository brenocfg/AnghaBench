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
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_3__ {int zc_nvlist_dst_size; scalar_t__ zc_nvlist_dst; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_objset_type; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 void* vmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (void*,int) ; 
 int xcopyout (void*,void*,int) ; 
 int zfs_userspace_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int*) ; 
 int zfsvfs_hold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsvfs_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_userspace_many(zfs_cmd_t *zc)
{
	zfsvfs_t *zfsvfs;
	int bufsize = zc->zc_nvlist_dst_size;

	if (bufsize <= 0)
		return (SET_ERROR(ENOMEM));

	int error = zfsvfs_hold(zc->zc_name, FTAG, &zfsvfs, B_FALSE);
	if (error != 0)
		return (error);

	void *buf = vmem_alloc(bufsize, KM_SLEEP);

	error = zfs_userspace_many(zfsvfs, zc->zc_objset_type, &zc->zc_cookie,
	    buf, &zc->zc_nvlist_dst_size);

	if (error == 0) {
		error = xcopyout(buf,
		    (void *)(uintptr_t)zc->zc_nvlist_dst,
		    zc->zc_nvlist_dst_size);
	}
	vmem_free(buf, bufsize);
	zfsvfs_rele(zfsvfs, FTAG);

	return (error);
}