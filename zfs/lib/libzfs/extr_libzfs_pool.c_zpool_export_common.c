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
struct TYPE_5__ {int /*<<< orphan*/  zpool_hdl; int /*<<< orphan*/  zpool_name; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_6__ {char* member_0; scalar_t__ zc_history; void* zc_guid; void* zc_cookie; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  void* boolean_t ;

/* Variables and functions */
#define  EXDEV 128 
 int /*<<< orphan*/  EZFS_ACTIVE_SPARE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_EXPORT ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int zpool_standard_error_fmt (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
zpool_export_common(zpool_handle_t *zhp, boolean_t force, boolean_t hardforce,
    const char *log_str)
{
	zfs_cmd_t zc = {"\0"};
	char msg[1024];

	(void) snprintf(msg, sizeof (msg), dgettext(TEXT_DOMAIN,
	    "cannot export '%s'"), zhp->zpool_name);

	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	zc.zc_cookie = force;
	zc.zc_guid = hardforce;
	zc.zc_history = (uint64_t)(uintptr_t)log_str;

	if (zfs_ioctl(zhp->zpool_hdl, ZFS_IOC_POOL_EXPORT, &zc) != 0) {
		switch (errno) {
		case EXDEV:
			zfs_error_aux(zhp->zpool_hdl, dgettext(TEXT_DOMAIN,
			    "use '-f' to override the following errors:\n"
			    "'%s' has an active shared spare which could be"
			    " used by other pools once '%s' is exported."),
			    zhp->zpool_name, zhp->zpool_name);
			return (zfs_error(zhp->zpool_hdl, EZFS_ACTIVE_SPARE,
			    msg));
		default:
			return (zpool_standard_error_fmt(zhp->zpool_hdl, errno,
			    msg));
		}
	}

	return (0);
}