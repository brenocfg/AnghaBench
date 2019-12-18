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
 int /*<<< orphan*/  VT_RELDISP ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int) ; 
 int vt_restore (int) ; 

int vt_release(int fd, bool restore) {
        assert(fd >= 0);

        /* This function releases the VT by acknowledging the VT-switch signal
         * sent by the kernel and optionally reset the VT in text and auto
         * VT-switching modes. */

        if (ioctl(fd, VT_RELDISP, 1) < 0)
                return -errno;

        if (restore)
                return vt_restore(fd);

        return 0;
}