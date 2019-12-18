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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  sub_version; } ;
struct TYPE_3__ {int /*<<< orphan*/  version; } ;
struct autofs_dev_ioctl {int ioctlfd; TYPE_2__ protosubver; TYPE_1__ protover; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_DEV_IOCTL_PROTOSUBVER ; 
 int /*<<< orphan*/  AUTOFS_DEV_IOCTL_PROTOVER ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  init_autofs_dev_ioctl (struct autofs_dev_ioctl*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct autofs_dev_ioctl*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int autofs_protocol(int dev_autofs_fd, int ioctl_fd) {
        uint32_t major, minor;
        struct autofs_dev_ioctl param;

        assert(dev_autofs_fd >= 0);
        assert(ioctl_fd >= 0);

        init_autofs_dev_ioctl(&param);
        param.ioctlfd = ioctl_fd;

        if (ioctl(dev_autofs_fd, AUTOFS_DEV_IOCTL_PROTOVER, &param) < 0)
                return -errno;

        major = param.protover.version;

        init_autofs_dev_ioctl(&param);
        param.ioctlfd = ioctl_fd;

        if (ioctl(dev_autofs_fd, AUTOFS_DEV_IOCTL_PROTOSUBVER, &param) < 0)
                return -errno;

        minor = param.protosubver.sub_version;

        log_debug("Autofs protocol version %i.%i", major, minor);
        return 0;
}