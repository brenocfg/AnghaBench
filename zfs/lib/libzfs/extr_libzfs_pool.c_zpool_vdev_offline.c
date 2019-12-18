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
struct TYPE_7__ {char* member_0; int /*<<< orphan*/  zc_obj; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
#define  EBUSY 129 
#define  EEXIST 128 
 int /*<<< orphan*/  EZFS_ISSPARE ; 
 int /*<<< orphan*/  EZFS_NODEVICE ; 
 int /*<<< orphan*/  EZFS_NOREPLICAS ; 
 int /*<<< orphan*/  EZFS_UNPLAYED_LOGS ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VDEV_STATE_OFFLINE ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SET_STATE ; 
 int /*<<< orphan*/  ZFS_OFFLINE_TEMPORARY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * zpool_find_vdev (TYPE_1__*,char const*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int zpool_standard_error (int /*<<< orphan*/ *,int,char*) ; 

int
zpool_vdev_offline(zpool_handle_t *zhp, const char *path, boolean_t istmp)
{
	zfs_cmd_t zc = {"\0"};
	char msg[1024];
	nvlist_t *tgt;
	boolean_t avail_spare, l2cache;
	libzfs_handle_t *hdl = zhp->zpool_hdl;

	(void) snprintf(msg, sizeof (msg),
	    dgettext(TEXT_DOMAIN, "cannot offline %s"), path);

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	if ((tgt = zpool_find_vdev(zhp, path, &avail_spare, &l2cache,
	    NULL)) == NULL)
		return (zfs_error(hdl, EZFS_NODEVICE, msg));

	verify(nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_GUID, &zc.zc_guid) == 0);

	if (avail_spare)
		return (zfs_error(hdl, EZFS_ISSPARE, msg));

	zc.zc_cookie = VDEV_STATE_OFFLINE;
	zc.zc_obj = istmp ? ZFS_OFFLINE_TEMPORARY : 0;

	if (zfs_ioctl(hdl, ZFS_IOC_VDEV_SET_STATE, &zc) == 0)
		return (0);

	switch (errno) {
	case EBUSY:

		/*
		 * There are no other replicas of this device.
		 */
		return (zfs_error(hdl, EZFS_NOREPLICAS, msg));

	case EEXIST:
		/*
		 * The log device has unplayed logs
		 */
		return (zfs_error(hdl, EZFS_UNPLAYED_LOGS, msg));

	default:
		return (zpool_standard_error(hdl, errno, msg));
	}
}