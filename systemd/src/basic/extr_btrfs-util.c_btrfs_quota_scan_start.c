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
struct btrfs_ioctl_quota_rescan_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_IOC_QUOTA_RESCAN ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct btrfs_ioctl_quota_rescan_args*) ; 

int btrfs_quota_scan_start(int fd) {
        struct btrfs_ioctl_quota_rescan_args args = {};

        assert(fd >= 0);

        if (ioctl(fd, BTRFS_IOC_QUOTA_RESCAN, &args) < 0)
                return -errno;

        return 0;
}