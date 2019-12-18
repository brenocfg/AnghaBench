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
struct TYPE_2__ {int /*<<< orphan*/  z_xattr_sa; int /*<<< orphan*/  z_flags; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ ZFS_XATTR_OFF ; 
 scalar_t__ ZFS_XATTR_SA ; 
 int /*<<< orphan*/  ZSB_XATTR ; 

__attribute__((used)) static void
xattr_changed_cb(void *arg, uint64_t newval)
{
	zfsvfs_t *zfsvfs = arg;

	if (newval == ZFS_XATTR_OFF) {
		zfsvfs->z_flags &= ~ZSB_XATTR;
	} else {
		zfsvfs->z_flags |= ZSB_XATTR;

		if (newval == ZFS_XATTR_SA)
			zfsvfs->z_xattr_sa = B_TRUE;
		else
			zfsvfs->z_xattr_sa = B_FALSE;
	}
}