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
 int /*<<< orphan*/  IN_CLOEXEC ; 
 int errno ; 
 scalar_t__ inotify_fd ; 
 scalar_t__ inotify_init1 (int /*<<< orphan*/ ) ; 

int udev_watch_init(void) {
        inotify_fd = inotify_init1(IN_CLOEXEC);
        if (inotify_fd < 0)
                return -errno;

        return inotify_fd;
}