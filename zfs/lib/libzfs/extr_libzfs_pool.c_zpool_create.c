#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* member_0; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  import; int /*<<< orphan*/  create; } ;
typedef  TYPE_2__ prop_flags_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  EBUSY 132 
#define  ENOSPC 131 
#define  ENOTBLK 130 
#define  EOVERFLOW 129 
#define  ERANGE 128 
 int /*<<< orphan*/  EZFS_BADDEV ; 
 int /*<<< orphan*/  EZFS_BADPROP ; 
 int /*<<< orphan*/  EZFS_CRYPTOFAILED ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  SPA_MINDEVSIZE ; 
 int /*<<< orphan*/  SPA_VERSION_1 ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_CREATE ; 
 int /*<<< orphan*/  ZFS_PROP_SPECIAL_SMALL_BLOCKS ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  ZPOOL_HIDDEN_ARGS ; 
 int /*<<< orphan*/  ZPOOL_ROOTFS_PROPS ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_uint8_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_1__*) ; 
 scalar_t__ zcmd_write_conf_nvlist (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zcmd_write_src_nvlist (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_crypto_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_nicebytes (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_valid_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zpool_has_special_vdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_name_valid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int zpool_standard_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * zpool_valid_proplist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__,char*) ; 

int
zpool_create(libzfs_handle_t *hdl, const char *pool, nvlist_t *nvroot,
    nvlist_t *props, nvlist_t *fsprops)
{
	zfs_cmd_t zc = {"\0"};
	nvlist_t *zc_fsprops = NULL;
	nvlist_t *zc_props = NULL;
	nvlist_t *hidden_args = NULL;
	uint8_t *wkeydata = NULL;
	uint_t wkeylen = 0;
	char msg[1024];
	int ret = -1;

	(void) snprintf(msg, sizeof (msg), dgettext(TEXT_DOMAIN,
	    "cannot create '%s'"), pool);

	if (!zpool_name_valid(hdl, B_FALSE, pool))
		return (zfs_error(hdl, EZFS_INVALIDNAME, msg));

	if (zcmd_write_conf_nvlist(hdl, &zc, nvroot) != 0)
		return (-1);

	if (props) {
		prop_flags_t flags = { .create = B_TRUE, .import = B_FALSE };

		if ((zc_props = zpool_valid_proplist(hdl, pool, props,
		    SPA_VERSION_1, flags, msg)) == NULL) {
			goto create_failed;
		}
	}

	if (fsprops) {
		uint64_t zoned;
		char *zonestr;

		zoned = ((nvlist_lookup_string(fsprops,
		    zfs_prop_to_name(ZFS_PROP_ZONED), &zonestr) == 0) &&
		    strcmp(zonestr, "on") == 0);

		if ((zc_fsprops = zfs_valid_proplist(hdl, ZFS_TYPE_FILESYSTEM,
		    fsprops, zoned, NULL, NULL, B_TRUE, msg)) == NULL) {
			goto create_failed;
		}

		if (nvlist_exists(zc_fsprops,
		    zfs_prop_to_name(ZFS_PROP_SPECIAL_SMALL_BLOCKS)) &&
		    !zpool_has_special_vdev(nvroot)) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "%s property requires a special vdev"),
			    zfs_prop_to_name(ZFS_PROP_SPECIAL_SMALL_BLOCKS));
			(void) zfs_error(hdl, EZFS_BADPROP, msg);
			goto create_failed;
		}

		if (!zc_props &&
		    (nvlist_alloc(&zc_props, NV_UNIQUE_NAME, 0) != 0)) {
			goto create_failed;
		}
		if (zfs_crypto_create(hdl, NULL, zc_fsprops, props, B_TRUE,
		    &wkeydata, &wkeylen) != 0) {
			zfs_error(hdl, EZFS_CRYPTOFAILED, msg);
			goto create_failed;
		}
		if (nvlist_add_nvlist(zc_props,
		    ZPOOL_ROOTFS_PROPS, zc_fsprops) != 0) {
			goto create_failed;
		}
		if (wkeydata != NULL) {
			if (nvlist_alloc(&hidden_args, NV_UNIQUE_NAME, 0) != 0)
				goto create_failed;

			if (nvlist_add_uint8_array(hidden_args, "wkeydata",
			    wkeydata, wkeylen) != 0)
				goto create_failed;

			if (nvlist_add_nvlist(zc_props, ZPOOL_HIDDEN_ARGS,
			    hidden_args) != 0)
				goto create_failed;
		}
	}

	if (zc_props && zcmd_write_src_nvlist(hdl, &zc, zc_props) != 0)
		goto create_failed;

	(void) strlcpy(zc.zc_name, pool, sizeof (zc.zc_name));

	if ((ret = zfs_ioctl(hdl, ZFS_IOC_POOL_CREATE, &zc)) != 0) {

		zcmd_free_nvlists(&zc);
		nvlist_free(zc_props);
		nvlist_free(zc_fsprops);
		nvlist_free(hidden_args);
		if (wkeydata != NULL)
			free(wkeydata);

		switch (errno) {
		case EBUSY:
			/*
			 * This can happen if the user has specified the same
			 * device multiple times.  We can't reliably detect this
			 * until we try to add it and see we already have a
			 * label.  This can also happen under if the device is
			 * part of an active md or lvm device.
			 */
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "one or more vdevs refer to the same device, or "
			    "one of\nthe devices is part of an active md or "
			    "lvm device"));
			return (zfs_error(hdl, EZFS_BADDEV, msg));

		case ERANGE:
			/*
			 * This happens if the record size is smaller or larger
			 * than the allowed size range, or not a power of 2.
			 *
			 * NOTE: although zfs_valid_proplist is called earlier,
			 * this case may have slipped through since the
			 * pool does not exist yet and it is therefore
			 * impossible to read properties e.g. max blocksize
			 * from the pool.
			 */
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "record size invalid"));
			return (zfs_error(hdl, EZFS_BADPROP, msg));

		case EOVERFLOW:
			/*
			 * This occurs when one of the devices is below
			 * SPA_MINDEVSIZE.  Unfortunately, we can't detect which
			 * device was the problem device since there's no
			 * reliable way to determine device size from userland.
			 */
			{
				char buf[64];

				zfs_nicebytes(SPA_MINDEVSIZE, buf,
				    sizeof (buf));

				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "one or more devices is less than the "
				    "minimum size (%s)"), buf);
			}
			return (zfs_error(hdl, EZFS_BADDEV, msg));

		case ENOSPC:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "one or more devices is out of space"));
			return (zfs_error(hdl, EZFS_BADDEV, msg));

		case ENOTBLK:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "cache device must be a disk or disk slice"));
			return (zfs_error(hdl, EZFS_BADDEV, msg));

		default:
			return (zpool_standard_error(hdl, errno, msg));
		}
	}

create_failed:
	zcmd_free_nvlists(&zc);
	nvlist_free(zc_props);
	nvlist_free(zc_fsprops);
	nvlist_free(hidden_args);
	if (wkeydata != NULL)
		free(wkeydata);
	return (ret);
}