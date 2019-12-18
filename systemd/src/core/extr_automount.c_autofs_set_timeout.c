#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct TYPE_2__ {scalar_t__ timeout; } ;
struct autofs_dev_ioctl {int ioctlfd; TYPE_1__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_DEV_IOCTL_TIMEOUT ; 
 scalar_t__ DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ USEC_INFINITY ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  init_autofs_dev_ioctl (struct autofs_dev_ioctl*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct autofs_dev_ioctl*) ; 

__attribute__((used)) static int autofs_set_timeout(int dev_autofs_fd, int ioctl_fd, usec_t usec) {
        struct autofs_dev_ioctl param;

        assert(dev_autofs_fd >= 0);
        assert(ioctl_fd >= 0);

        init_autofs_dev_ioctl(&param);
        param.ioctlfd = ioctl_fd;

        if (usec == USEC_INFINITY)
                param.timeout.timeout = 0;
        else
                /* Convert to seconds, rounding up. */
                param.timeout.timeout = DIV_ROUND_UP(usec, USEC_PER_SEC);

        if (ioctl(dev_autofs_fd, AUTOFS_DEV_IOCTL_TIMEOUT, &param) < 0)
                return -errno;

        return 0;
}