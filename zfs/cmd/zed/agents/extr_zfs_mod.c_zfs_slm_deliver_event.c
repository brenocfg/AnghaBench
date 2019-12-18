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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EC_DEV_ADD ; 
 int /*<<< orphan*/  EC_DEV_STATUS ; 
 int /*<<< orphan*/  EC_ZFS ; 
 int /*<<< orphan*/  ESC_DEV_DLE ; 
 int /*<<< orphan*/  ESC_DISK ; 
 int /*<<< orphan*/  ESC_LOFI ; 
 int /*<<< orphan*/  ESC_ZFS_VDEV_CHECK ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int zfs_deliver_add (int /*<<< orphan*/ *,scalar_t__) ; 
 int zfs_deliver_check (int /*<<< orphan*/ *) ; 
 int zfs_deliver_dle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_slm_deliver_event(const char *class, const char *subclass, nvlist_t *nvl)
{
	int ret;
	boolean_t is_lofi = B_FALSE, is_check = B_FALSE, is_dle = B_FALSE;

	if (strcmp(class, EC_DEV_ADD) == 0) {
		/*
		 * We're mainly interested in disk additions, but we also listen
		 * for new loop devices, to allow for simplified testing.
		 */
		if (strcmp(subclass, ESC_DISK) == 0)
			is_lofi = B_FALSE;
		else if (strcmp(subclass, ESC_LOFI) == 0)
			is_lofi = B_TRUE;
		else
			return (0);

		is_check = B_FALSE;
	} else if (strcmp(class, EC_ZFS) == 0 &&
	    strcmp(subclass, ESC_ZFS_VDEV_CHECK) == 0) {
		/*
		 * This event signifies that a device failed to open
		 * during pool load, but the 'autoreplace' property was
		 * set, so we should pretend it's just been added.
		 */
		is_check = B_TRUE;
	} else if (strcmp(class, EC_DEV_STATUS) == 0 &&
	    strcmp(subclass, ESC_DEV_DLE) == 0) {
		is_dle = B_TRUE;
	} else {
		return (0);
	}

	if (is_dle)
		ret = zfs_deliver_dle(nvl);
	else if (is_check)
		ret = zfs_deliver_check(nvl);
	else
		ret = zfs_deliver_add(nvl, is_lofi);

	return (ret);
}