#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ zpool_state; int /*<<< orphan*/  zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_6__ {char* member_0; scalar_t__ zc_history; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 scalar_t__ EROFS ; 
 int /*<<< orphan*/  EZFS_BADDEV ; 
 scalar_t__ POOL_STATE_ACTIVE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_DESTROY ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  remove_mountpoint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_standard_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 

int
zpool_destroy(zpool_handle_t *zhp, const char *log_str)
{
	zfs_cmd_t zc = {"\0"};
	zfs_handle_t *zfp = NULL;
	libzfs_handle_t *hdl = zhp->zpool_hdl;
	char msg[1024];

	if (zhp->zpool_state == POOL_STATE_ACTIVE &&
	    (zfp = zfs_open(hdl, zhp->zpool_name, ZFS_TYPE_FILESYSTEM)) == NULL)
		return (-1);

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	zc.zc_history = (uint64_t)(uintptr_t)log_str;

	if (zfs_ioctl(hdl, ZFS_IOC_POOL_DESTROY, &zc) != 0) {
		(void) snprintf(msg, sizeof (msg), dgettext(TEXT_DOMAIN,
		    "cannot destroy '%s'"), zhp->zpool_name);

		if (errno == EROFS) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "one or more devices is read only"));
			(void) zfs_error(hdl, EZFS_BADDEV, msg);
		} else {
			(void) zpool_standard_error(hdl, errno, msg);
		}

		if (zfp)
			zfs_close(zfp);
		return (-1);
	}

	if (zfp) {
		remove_mountpoint(zfp);
		zfs_close(zfp);
	}

	return (0);
}