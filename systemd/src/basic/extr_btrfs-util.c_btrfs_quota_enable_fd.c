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
struct btrfs_ioctl_quota_ctl_args {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_IOC_QUOTA_CTL ; 
 int /*<<< orphan*/  BTRFS_QUOTA_CTL_DISABLE ; 
 int /*<<< orphan*/  BTRFS_QUOTA_CTL_ENABLE ; 
 int ENOTTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int btrfs_is_filesystem (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct btrfs_ioctl_quota_ctl_args*) ; 

int btrfs_quota_enable_fd(int fd, bool b) {
        struct btrfs_ioctl_quota_ctl_args args = {
                .cmd = b ? BTRFS_QUOTA_CTL_ENABLE : BTRFS_QUOTA_CTL_DISABLE,
        };
        int r;

        assert(fd >= 0);

        r = btrfs_is_filesystem(fd);
        if (r < 0)
                return r;
        if (!r)
                return -ENOTTY;

        if (ioctl(fd, BTRFS_IOC_QUOTA_CTL, &args) < 0)
                return -errno;

        return 0;
}