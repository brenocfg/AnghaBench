#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_3__ {void* token; } ;
struct TYPE_4__ {int status; void* token; } ;
struct autofs_dev_ioctl {int ioctlfd; TYPE_1__ ready; TYPE_2__ fail; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_DEV_IOCTL_FAIL ; 
 int /*<<< orphan*/  AUTOFS_DEV_IOCTL_READY ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  init_autofs_dev_ioctl (struct autofs_dev_ioctl*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct autofs_dev_ioctl*) ; 

__attribute__((used)) static int autofs_send_ready(int dev_autofs_fd, int ioctl_fd, uint32_t token, int status) {
        struct autofs_dev_ioctl param;

        assert(dev_autofs_fd >= 0);
        assert(ioctl_fd >= 0);

        init_autofs_dev_ioctl(&param);
        param.ioctlfd = ioctl_fd;

        if (status != 0) {
                param.fail.token = token;
                param.fail.status = status;
        } else
                param.ready.token = token;

        if (ioctl(dev_autofs_fd, status ? AUTOFS_DEV_IOCTL_FAIL : AUTOFS_DEV_IOCTL_READY, &param) < 0)
                return -errno;

        return 0;
}