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
 int /*<<< orphan*/  BTRFS_IOC_CLONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int fd_verify_regular (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int) ; 

int btrfs_reflink(int infd, int outfd) {
        int r;

        assert(infd >= 0);
        assert(outfd >= 0);

        /* Make sure we invoke the ioctl on a regular file, so that no device driver accidentally gets it. */

        r = fd_verify_regular(outfd);
        if (r < 0)
                return r;

        if (ioctl(outfd, BTRFS_IOC_CLONE, infd) < 0)
                return -errno;

        return 0;
}