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
 int /*<<< orphan*/  DRM_IOCTL_SET_MASTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_drmsetmaster(int fd) {
        assert(fd >= 0);

        if (ioctl(fd, DRM_IOCTL_SET_MASTER, 0) < 0)
                return -errno;

        return 0;
}