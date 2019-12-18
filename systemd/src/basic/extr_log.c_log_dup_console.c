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
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int console_fd ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 

int log_dup_console(void) {
        int copy;

        /* Duplicate the fd we use for fd logging if it's < 3 and use the copy from now on. This call is useful
         * whenever we want to continue logging through the original fd, but want to rearrange stderr. */

        if (console_fd >= 3)
                return 0;

        copy = fcntl(console_fd, F_DUPFD_CLOEXEC, 3);
        if (copy < 0)
                return -errno;

        console_fd = copy;
        return 0;
}