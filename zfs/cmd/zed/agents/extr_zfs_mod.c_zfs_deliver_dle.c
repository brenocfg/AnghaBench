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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PHYS_PATH ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_EV_VDEV_GUID ; 
 int /*<<< orphan*/  g_zfshdl ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  zfs_append_partition (char*,int) ; 
 int /*<<< orphan*/  zfsdle_vdev_online ; 
 int zpool_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
zfs_deliver_dle(nvlist_t *nvl)
{
	char *devname, name[MAXPATHLEN];
	uint64_t guid;

	if (nvlist_lookup_uint64(nvl, ZFS_EV_VDEV_GUID, &guid) == 0) {
		sprintf(name, "%llu", (u_longlong_t)guid);
	} else if (nvlist_lookup_string(nvl, DEV_PHYS_PATH, &devname) == 0) {
		strlcpy(name, devname, MAXPATHLEN);
		zfs_append_partition(name, MAXPATHLEN);
	} else {
		zed_log_msg(LOG_INFO, "zfs_deliver_dle: no guid or physpath");
	}

	if (zpool_iter(g_zfshdl, zfsdle_vdev_online, name) != 1) {
		zed_log_msg(LOG_INFO, "zfs_deliver_dle: device '%s' not "
		    "found", name);
		return (1);
	}

	return (0);
}