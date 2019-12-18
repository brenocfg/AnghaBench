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
struct zed_conf {int zevent_fd; int /*<<< orphan*/ * zfs_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_disk_event_fini () ; 
 int /*<<< orphan*/  zed_log_die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_agent_fini () ; 

void
zed_event_fini(struct zed_conf *zcp)
{
	if (!zcp)
		zed_log_die("Failed zed_event_fini: %s", strerror(EINVAL));

	zed_disk_event_fini();
	zfs_agent_fini();

	if (zcp->zevent_fd >= 0) {
		if (close(zcp->zevent_fd) < 0)
			zed_log_msg(LOG_WARNING, "Failed to close \"%s\": %s",
			    ZFS_DEV, strerror(errno));

		zcp->zevent_fd = -1;
	}
	if (zcp->zfs_hdl) {
		libzfs_fini(zcp->zfs_hdl);
		zcp->zfs_hdl = NULL;
	}
}