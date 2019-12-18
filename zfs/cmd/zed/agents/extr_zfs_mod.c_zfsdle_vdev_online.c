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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  vdev_state_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fullpath ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAXPATHLEN ; 
 scalar_t__ POOL_STATE_UNAVAIL ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_WHOLE_DISK ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOEXPAND ; 
 int /*<<< orphan*/  free (char*) ; 
 int nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 
 char* zfs_strip_partition (char*) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_find_vdev_by_physpath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_reopen_one (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpool_vdev_online (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfsdle_vdev_online(zpool_handle_t *zhp, void *data)
{
	char *devname = data;
	boolean_t avail_spare, l2cache;
	nvlist_t *tgt;
	int error;

	zed_log_msg(LOG_INFO, "zfsdle_vdev_online: searching for '%s' in '%s'",
	    devname, zpool_get_name(zhp));

	if ((tgt = zpool_find_vdev_by_physpath(zhp, devname,
	    &avail_spare, &l2cache, NULL)) != NULL) {
		char *path, fullpath[MAXPATHLEN];
		uint64_t wholedisk;

		error = nvlist_lookup_string(tgt, ZPOOL_CONFIG_PATH, &path);
		if (error) {
			zpool_close(zhp);
			return (0);
		}

		error = nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_WHOLE_DISK,
		    &wholedisk);
		if (error)
			wholedisk = 0;

		if (wholedisk) {
			path = strrchr(path, '/');
			if (path != NULL) {
				path = zfs_strip_partition(path + 1);
				if (path == NULL) {
					zpool_close(zhp);
					return (0);
				}
			} else {
				zpool_close(zhp);
				return (0);
			}

			(void) strlcpy(fullpath, path, sizeof (fullpath));
			free(path);

			/*
			 * We need to reopen the pool associated with this
			 * device so that the kernel can update the size of
			 * the expanded device.  When expanding there is no
			 * need to restart the scrub from the beginning.
			 */
			boolean_t scrub_restart = B_FALSE;
			(void) zpool_reopen_one(zhp, &scrub_restart);
		} else {
			(void) strlcpy(fullpath, path, sizeof (fullpath));
		}

		if (zpool_get_prop_int(zhp, ZPOOL_PROP_AUTOEXPAND, NULL)) {
			vdev_state_t newstate;

			if (zpool_get_state(zhp) != POOL_STATE_UNAVAIL) {
				error = zpool_vdev_online(zhp, fullpath, 0,
				    &newstate);
				zed_log_msg(LOG_INFO, "zfsdle_vdev_online: "
				    "setting device '%s' to ONLINE state "
				    "in pool '%s': %d", fullpath,
				    zpool_get_name(zhp), error);
			}
		}
		zpool_close(zhp);
		return (1);
	}
	zpool_close(zhp);
	return (0);
}