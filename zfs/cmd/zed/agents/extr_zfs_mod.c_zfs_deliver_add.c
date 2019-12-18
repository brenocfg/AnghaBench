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
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_IDENTIFIER ; 
 int /*<<< orphan*/  DEV_IS_PART ; 
 int /*<<< orphan*/  DEV_PHYS_PATH ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  devid_iter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devphys_iter (char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvlist_lookup_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char*,char*,int) ; 
 int /*<<< orphan*/  zfs_process_add ; 

__attribute__((used)) static int
zfs_deliver_add(nvlist_t *nvl, boolean_t is_lofi)
{
	char *devpath = NULL, *devid;
	boolean_t is_slice;

	/*
	 * Expecting a devid string and an optional physical location
	 */
	if (nvlist_lookup_string(nvl, DEV_IDENTIFIER, &devid) != 0)
		return (-1);

	(void) nvlist_lookup_string(nvl, DEV_PHYS_PATH, &devpath);

	is_slice = (nvlist_lookup_boolean(nvl, DEV_IS_PART) == 0);

	zed_log_msg(LOG_INFO, "zfs_deliver_add: adding %s (%s) (is_slice %d)",
	    devid, devpath ? devpath : "NULL", is_slice);

	/*
	 * Iterate over all vdevs looking for a match in the following order:
	 * 1. ZPOOL_CONFIG_DEVID (identifies the unique disk)
	 * 2. ZPOOL_CONFIG_PHYS_PATH (identifies disk physical location).
	 *
	 * For disks, we only want to pay attention to vdevs marked as whole
	 * disks or are a multipath device.
	 */
	if (!devid_iter(devid, zfs_process_add, is_slice) && devpath != NULL)
		(void) devphys_iter(devpath, devid, zfs_process_add, is_slice);

	return (0);
}