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
 int /*<<< orphan*/  KDSKBMODE ; 
 int K_UNICODE ; 
 int K_XLATE ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vt_default_utf8 () ; 

int vt_reset_keyboard(int fd) {
        int kb;

        /* If we can't read the default, then default to unicode. It's 2017 after all. */
        kb = vt_default_utf8() != 0 ? K_UNICODE : K_XLATE;

        if (ioctl(fd, KDSKBMODE, kb) < 0)
                return -errno;

        return 0;
}