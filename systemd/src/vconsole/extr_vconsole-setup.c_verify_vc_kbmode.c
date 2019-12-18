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
 int EBUSY ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KDGKBMODE ; 
 int /*<<< orphan*/  K_UNICODE ; 
 int /*<<< orphan*/  K_XLATE ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int verify_vc_kbmode(int fd) {
        int curr_mode;

        /*
         * Make sure we only adjust consoles in K_XLATE or K_UNICODE mode.
         * Otherwise we would (likely) interfere with X11's processing of the
         * key events.
         *
         * http://lists.freedesktop.org/archives/systemd-devel/2013-February/008573.html
         */

        if (ioctl(fd, KDGKBMODE, &curr_mode) < 0)
                return -errno;

        return IN_SET(curr_mode, K_XLATE, K_UNICODE) ? 0 : -EBUSY;
}