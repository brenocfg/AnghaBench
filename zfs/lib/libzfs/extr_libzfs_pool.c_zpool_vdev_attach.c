#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_12__ {char* member_0; int zc_cookie; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
#define  EBUSY 133 
#define  EDOM 132 
#define  EINVAL 131 
#define  ENAMETOOLONG 130 
#define  ENOTSUP 129 
#define  EOVERFLOW 128 
 int /*<<< orphan*/  EZFS_BADDEV ; 
 int /*<<< orphan*/  EZFS_BADTARGET ; 
 int /*<<< orphan*/  EZFS_DEVOVERFLOW ; 
 int /*<<< orphan*/  EZFS_INVALCONFIG ; 
 int /*<<< orphan*/  EZFS_ISL2CACHE ; 
 int /*<<< orphan*/  EZFS_ISSPARE ; 
 int /*<<< orphan*/  EZFS_NODEVICE ; 
 int /*<<< orphan*/  SPA_VERSION_MULTI_REPLACE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_ATTACH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_SPARE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  ZPOOL_PROP_VERSION ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_replacing_spare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 
 scalar_t__ zcmd_write_conf_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * zpool_find_vdev (TYPE_1__*,char const*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  zpool_get_config (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_prop_int (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_is_bootable (TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_standard_error (int /*<<< orphan*/ *,int,char*) ; 
 char* zpool_vdev_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zpool_vdev_attach(zpool_handle_t *zhp,
    const char *old_disk, const char *new_disk, nvlist_t *nvroot, int replacing)
{
	zfs_cmd_t zc = {"\0"};
	char msg[1024];
	int ret;
	nvlist_t *tgt;
	boolean_t avail_spare, l2cache, islog;
	uint64_t val;
	char *newname;
	nvlist_t **child;
	uint_t children;
	nvlist_t *config_root;
	libzfs_handle_t *hdl = zhp->zpool_hdl;
	boolean_t rootpool = zpool_is_bootable(zhp);

	if (replacing)
		(void) snprintf(msg, sizeof (msg), dgettext(TEXT_DOMAIN,
		    "cannot replace %s with %s"), old_disk, new_disk);
	else
		(void) snprintf(msg, sizeof (msg), dgettext(TEXT_DOMAIN,
		    "cannot attach %s to %s"), new_disk, old_disk);

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	if ((tgt = zpool_find_vdev(zhp, old_disk, &avail_spare, &l2cache,
	    &islog)) == NULL)
		return (zfs_error(hdl, EZFS_NODEVICE, msg));

	if (avail_spare)
		return (zfs_error(hdl, EZFS_ISSPARE, msg));

	if (l2cache)
		return (zfs_error(hdl, EZFS_ISL2CACHE, msg));

	verify(nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_GUID, &zc.zc_guid) == 0);
	zc.zc_cookie = replacing;

	if (nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_CHILDREN,
	    &child, &children) != 0 || children != 1) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "new device must be a single disk"));
		return (zfs_error(hdl, EZFS_INVALCONFIG, msg));
	}

	verify(nvlist_lookup_nvlist(zpool_get_config(zhp, NULL),
	    ZPOOL_CONFIG_VDEV_TREE, &config_root) == 0);

	if ((newname = zpool_vdev_name(NULL, NULL, child[0], 0)) == NULL)
		return (-1);

	/*
	 * If the target is a hot spare that has been swapped in, we can only
	 * replace it with another hot spare.
	 */
	if (replacing &&
	    nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_IS_SPARE, &val) == 0 &&
	    (zpool_find_vdev(zhp, newname, &avail_spare, &l2cache,
	    NULL) == NULL || !avail_spare) &&
	    is_replacing_spare(config_root, tgt, 1)) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "can only be replaced by another hot spare"));
		free(newname);
		return (zfs_error(hdl, EZFS_BADTARGET, msg));
	}

	free(newname);

	if (zcmd_write_conf_nvlist(hdl, &zc, nvroot) != 0)
		return (-1);

	ret = zfs_ioctl(hdl, ZFS_IOC_VDEV_ATTACH, &zc);

	zcmd_free_nvlists(&zc);

	if (ret == 0) {
		if (rootpool) {
			/*
			 * XXX need a better way to prevent user from
			 * booting up a half-baked vdev.
			 */
			(void) fprintf(stderr, dgettext(TEXT_DOMAIN, "Make "
			    "sure to wait until resilver is done "
			    "before rebooting.\n"));
		}
		return (0);
	}

	switch (errno) {
	case ENOTSUP:
		/*
		 * Can't attach to or replace this type of vdev.
		 */
		if (replacing) {
			uint64_t version = zpool_get_prop_int(zhp,
			    ZPOOL_PROP_VERSION, NULL);

			if (islog)
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "cannot replace a log with a spare"));
			else if (version >= SPA_VERSION_MULTI_REPLACE)
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "already in replacing/spare config; wait "
				    "for completion or use 'zpool detach'"));
			else
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "cannot replace a replacing device"));
		} else {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "can only attach to mirrors and top-level "
			    "disks"));
		}
		(void) zfs_error(hdl, EZFS_BADTARGET, msg);
		break;

	case EINVAL:
		/*
		 * The new device must be a single disk.
		 */
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "new device must be a single disk"));
		(void) zfs_error(hdl, EZFS_INVALCONFIG, msg);
		break;

	case EBUSY:
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "%s is busy, "
		    "or device removal is in progress"),
		    new_disk);
		(void) zfs_error(hdl, EZFS_BADDEV, msg);
		break;

	case EOVERFLOW:
		/*
		 * The new device is too small.
		 */
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "device is too small"));
		(void) zfs_error(hdl, EZFS_BADDEV, msg);
		break;

	case EDOM:
		/*
		 * The new device has a different optimal sector size.
		 */
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "new device has a different optimal sector size; use the "
		    "option '-o ashift=N' to override the optimal size"));
		(void) zfs_error(hdl, EZFS_BADDEV, msg);
		break;

	case ENAMETOOLONG:
		/*
		 * The resulting top-level vdev spec won't fit in the label.
		 */
		(void) zfs_error(hdl, EZFS_DEVOVERFLOW, msg);
		break;

	default:
		(void) zpool_standard_error(hdl, errno, msg);
	}

	return (-1);
}