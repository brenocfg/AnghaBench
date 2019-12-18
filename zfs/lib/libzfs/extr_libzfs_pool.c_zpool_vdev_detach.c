#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_7__ {char* member_0; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
#define  EBUSY 129 
#define  ENOTSUP 128 
 int /*<<< orphan*/  EZFS_BADTARGET ; 
 int /*<<< orphan*/  EZFS_ISL2CACHE ; 
 int /*<<< orphan*/  EZFS_ISSPARE ; 
 int /*<<< orphan*/  EZFS_NODEVICE ; 
 int /*<<< orphan*/  EZFS_NOREPLICAS ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_DETACH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * zpool_find_vdev (TYPE_1__*,char const*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_standard_error (int /*<<< orphan*/ *,int,char*) ; 

int
zpool_vdev_detach(zpool_handle_t *zhp, const char *path)
{
	zfs_cmd_t zc = {"\0"};
	char msg[1024];
	nvlist_t *tgt;
	boolean_t avail_spare, l2cache;
	libzfs_handle_t *hdl = zhp->zpool_hdl;

	(void) snprintf(msg, sizeof (msg),
	    dgettext(TEXT_DOMAIN, "cannot detach %s"), path);

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	if ((tgt = zpool_find_vdev(zhp, path, &avail_spare, &l2cache,
	    NULL)) == NULL)
		return (zfs_error(hdl, EZFS_NODEVICE, msg));

	if (avail_spare)
		return (zfs_error(hdl, EZFS_ISSPARE, msg));

	if (l2cache)
		return (zfs_error(hdl, EZFS_ISL2CACHE, msg));

	verify(nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_GUID, &zc.zc_guid) == 0);

	if (zfs_ioctl(hdl, ZFS_IOC_VDEV_DETACH, &zc) == 0)
		return (0);

	switch (errno) {

	case ENOTSUP:
		/*
		 * Can't detach from this type of vdev.
		 */
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "only "
		    "applicable to mirror and replacing vdevs"));
		(void) zfs_error(hdl, EZFS_BADTARGET, msg);
		break;

	case EBUSY:
		/*
		 * There are no other replicas of this device.
		 */
		(void) zfs_error(hdl, EZFS_NOREPLICAS, msg);
		break;

	default:
		(void) zpool_standard_error(hdl, errno, msg);
	}

	return (-1);
}