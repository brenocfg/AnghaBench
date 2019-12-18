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
struct zed_conf {scalar_t__ zevent_fd; int /*<<< orphan*/  zfs_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libzfs_init () ; 
 scalar_t__ open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ zed_disk_event_init () ; 
 int /*<<< orphan*/  zed_log_die (char*,...) ; 
 int /*<<< orphan*/  zfs_agent_init (int /*<<< orphan*/ ) ; 

void
zed_event_init(struct zed_conf *zcp)
{
	if (!zcp)
		zed_log_die("Failed zed_event_init: %s", strerror(EINVAL));

	zcp->zfs_hdl = libzfs_init();
	if (!zcp->zfs_hdl)
		zed_log_die("Failed to initialize libzfs");

	zcp->zevent_fd = open(ZFS_DEV, O_RDWR);
	if (zcp->zevent_fd < 0)
		zed_log_die("Failed to open \"%s\": %s",
		    ZFS_DEV, strerror(errno));

	zfs_agent_init(zcp->zfs_hdl);

	if (zed_disk_event_init() != 0)
		zed_log_die("Failed to initialize disk events");
}