#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct autofs_dev_ioctl {int /*<<< orphan*/  ver_minor; int /*<<< orphan*/  ver_major; } ;
struct TYPE_4__ {scalar_t__ dev_autofs_fd; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_DEV_IOCTL_VERSION ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  init_autofs_dev_ioctl (struct autofs_dev_ioctl*) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,struct autofs_dev_ioctl*) ; 
 int /*<<< orphan*/  label_fix (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*) ; 
 int open (char*,int) ; 
 scalar_t__ safe_close (scalar_t__) ; 

__attribute__((used)) static int open_dev_autofs(Manager *m) {
        struct autofs_dev_ioctl param;

        assert(m);

        if (m->dev_autofs_fd >= 0)
                return m->dev_autofs_fd;

        (void) label_fix("/dev/autofs", 0);

        m->dev_autofs_fd = open("/dev/autofs", O_CLOEXEC|O_RDONLY);
        if (m->dev_autofs_fd < 0)
                return log_error_errno(errno, "Failed to open /dev/autofs: %m");

        init_autofs_dev_ioctl(&param);
        if (ioctl(m->dev_autofs_fd, AUTOFS_DEV_IOCTL_VERSION, &param) < 0) {
                m->dev_autofs_fd = safe_close(m->dev_autofs_fd);
                return -errno;
        }

        log_debug("Autofs kernel version %i.%i", param.ver_major, param.ver_minor);

        return m->dev_autofs_fd;
}