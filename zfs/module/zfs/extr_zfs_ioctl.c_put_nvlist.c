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
struct TYPE_3__ {size_t zc_nvlist_dst_size; int /*<<< orphan*/  zc_nvlist_dst_filled; int /*<<< orphan*/  zc_iflags; scalar_t__ zc_nvlist_dst; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ddi_copyout (char*,void*,size_t,int /*<<< orphan*/ ) ; 
 char* fnvlist_pack (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  fnvlist_pack_free (char*,size_t) ; 
 size_t fnvlist_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
put_nvlist(zfs_cmd_t *zc, nvlist_t *nvl)
{
	char *packed = NULL;
	int error = 0;
	size_t size;

	size = fnvlist_size(nvl);

	if (size > zc->zc_nvlist_dst_size) {
		error = SET_ERROR(ENOMEM);
	} else {
		packed = fnvlist_pack(nvl, &size);
		if (ddi_copyout(packed, (void *)(uintptr_t)zc->zc_nvlist_dst,
		    size, zc->zc_iflags) != 0)
			error = SET_ERROR(EFAULT);
		fnvlist_pack_free(packed, size);
	}

	zc->zc_nvlist_dst_size = size;
	zc->zc_nvlist_dst_filled = B_TRUE;
	return (error);
}