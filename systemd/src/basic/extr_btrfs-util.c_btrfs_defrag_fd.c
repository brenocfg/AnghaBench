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

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_IOC_DEFRAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int fd_verify_regular (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_defrag_fd(int fd) {
        int r;

        assert(fd >= 0);

        r = fd_verify_regular(fd);
        if (r < 0)
                return r;

        if (ioctl(fd, BTRFS_IOC_DEFRAG, NULL) < 0)
                return -errno;

        return 0;
}