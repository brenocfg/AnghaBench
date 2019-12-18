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
struct TYPE_3__ {char* vds_devid; char* vds_devphys; } ;
typedef  TYPE_1__ vdev_dev_strs_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  VDEV_TYPE_DISK ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_DEVID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PHYS_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_ENC_SYSFS_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_WHOLE_DISK ; 
 scalar_t__ encode_device_strings (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nvlist_remove_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* zfs_get_enclosure_sysfs_path (char*) ; 
 char* zfs_get_underlying_path (char*) ; 

void
update_vdev_config_dev_strs(nvlist_t *nv)
{
	vdev_dev_strs_t vds;
	char *env, *type, *path;
	uint64_t wholedisk = 0;
	char *upath, *spath;

	/*
	 * For the benefit of legacy ZFS implementations, allow
	 * for opting out of devid strings in the vdev label.
	 *
	 * example use:
	 *	env ZFS_VDEV_DEVID_OPT_OUT=YES zpool import dozer
	 *
	 * explanation:
	 * Older ZFS on Linux implementations had issues when attempting to
	 * display pool config VDEV names if a "devid" NVP value is present
	 * in the pool's config.
	 *
	 * For example, a pool that originated on illumos platform would
	 * have a devid value in the config and "zpool status" would fail
	 * when listing the config.
	 *
	 * A pool can be stripped of any "devid" values on import or
	 * prevented from adding them on zpool create|add by setting
	 * ZFS_VDEV_DEVID_OPT_OUT.
	 */
	env = getenv("ZFS_VDEV_DEVID_OPT_OUT");
	if (env && (strtoul(env, NULL, 0) > 0 ||
	    !strncasecmp(env, "YES", 3) || !strncasecmp(env, "ON", 2))) {
		(void) nvlist_remove_all(nv, ZPOOL_CONFIG_DEVID);
		(void) nvlist_remove_all(nv, ZPOOL_CONFIG_PHYS_PATH);
		return;
	}

	if (nvlist_lookup_string(nv, ZPOOL_CONFIG_TYPE, &type) != 0 ||
	    strcmp(type, VDEV_TYPE_DISK) != 0) {
		return;
	}
	if (nvlist_lookup_string(nv, ZPOOL_CONFIG_PATH, &path) != 0)
		return;
	(void) nvlist_lookup_uint64(nv, ZPOOL_CONFIG_WHOLE_DISK, &wholedisk);

	/*
	 * Update device string values in the config nvlist.
	 */
	if (encode_device_strings(path, &vds, (boolean_t)wholedisk) == 0) {
		(void) nvlist_add_string(nv, ZPOOL_CONFIG_DEVID, vds.vds_devid);
		if (vds.vds_devphys[0] != '\0') {
			(void) nvlist_add_string(nv, ZPOOL_CONFIG_PHYS_PATH,
			    vds.vds_devphys);
		}

		/* Add enclosure sysfs path (if disk is in an enclosure). */
		upath = zfs_get_underlying_path(path);
		spath = zfs_get_enclosure_sysfs_path(upath);
		if (spath)
			nvlist_add_string(nv, ZPOOL_CONFIG_VDEV_ENC_SYSFS_PATH,
			    spath);
		else
			nvlist_remove_all(nv, ZPOOL_CONFIG_VDEV_ENC_SYSFS_PATH);

		free(upath);
		free(spath);
	} else {
		/* Clear out any stale entries. */
		(void) nvlist_remove_all(nv, ZPOOL_CONFIG_DEVID);
		(void) nvlist_remove_all(nv, ZPOOL_CONFIG_PHYS_PATH);
		(void) nvlist_remove_all(nv, ZPOOL_CONFIG_VDEV_ENC_SYSFS_PATH);
	}
}