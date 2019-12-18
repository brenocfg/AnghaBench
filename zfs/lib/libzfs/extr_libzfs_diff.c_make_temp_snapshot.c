#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* member_0; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_cleanup_fd; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  tmpsnap; int /*<<< orphan*/  ds; int /*<<< orphan*/  tosnap; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  cleanupfd; TYPE_1__* zhp; } ;
typedef  TYPE_3__ differ_info_t ;
struct TYPE_6__ {int /*<<< orphan*/ * zfs_hdl; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  EZFS_DIFF ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* ZDIFF_PREFIX ; 
 int /*<<< orphan*/  ZFS_IOC_TMP_SNAPSHOT ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_temp_snapshot(differ_info_t *di)
{
	libzfs_handle_t *hdl = di->zhp->zfs_hdl;
	zfs_cmd_t zc = {"\0"};

	(void) snprintf(zc.zc_value, sizeof (zc.zc_value),
	    ZDIFF_PREFIX, getpid());
	(void) strlcpy(zc.zc_name, di->ds, sizeof (zc.zc_name));
	zc.zc_cleanup_fd = di->cleanupfd;

	if (zfs_ioctl(hdl, ZFS_IOC_TMP_SNAPSHOT, &zc) != 0) {
		int err = errno;
		if (err == EPERM) {
			(void) snprintf(di->errbuf, sizeof (di->errbuf),
			    dgettext(TEXT_DOMAIN, "The diff delegated "
			    "permission is needed in order\nto create a "
			    "just-in-time snapshot for diffing\n"));
			return (zfs_error(hdl, EZFS_DIFF, di->errbuf));
		} else {
			(void) snprintf(di->errbuf, sizeof (di->errbuf),
			    dgettext(TEXT_DOMAIN, "Cannot create just-in-time "
			    "snapshot of '%s'"), zc.zc_name);
			return (zfs_standard_error(hdl, err, di->errbuf));
		}
	}

	di->tmpsnap = zfs_strdup(hdl, zc.zc_value);
	di->tosnap = zfs_asprintf(hdl, "%s@%s", di->ds, di->tmpsnap);
	return (0);
}