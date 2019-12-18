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
typedef  int /*<<< orphan*/  uint64_t ;
struct btrfs_ioctl_qgroup_assign_args {int assign; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_IOC_QGROUP_ASSIGN ; 
 int EBUSY ; 
 int ENOTTY ; 
 int btrfs_is_filesystem (int) ; 
 int /*<<< orphan*/  btrfs_quota_scan_start (int) ; 
 int /*<<< orphan*/  btrfs_quota_scan_wait (int) ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct btrfs_ioctl_qgroup_assign_args*) ; 

__attribute__((used)) static int qgroup_assign_or_unassign(int fd, bool b, uint64_t child, uint64_t parent) {
        struct btrfs_ioctl_qgroup_assign_args args = {
                .assign = b,
                .src = child,
                .dst = parent,
        };
        unsigned c;
        int r;

        r = btrfs_is_filesystem(fd);
        if (r < 0)
                return r;
        if (r == 0)
                return -ENOTTY;

        for (c = 0;; c++) {
                r = ioctl(fd, BTRFS_IOC_QGROUP_ASSIGN, &args);
                if (r < 0) {
                        if (errno == EBUSY && c < 10) {
                                (void) btrfs_quota_scan_wait(fd);
                                continue;
                        }

                        return -errno;
                }

                if (r == 0)
                        return 0;

                /* If the return value is > 0, we need to request a rescan */

                (void) btrfs_quota_scan_start(fd);
                return 1;
        }
}