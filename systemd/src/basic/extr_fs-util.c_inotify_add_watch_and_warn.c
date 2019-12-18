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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ ENOSPC ; 
 scalar_t__ errno ; 
 scalar_t__ inotify_add_watch (int,char const*,int /*<<< orphan*/ ) ; 
 int log_error_errno (scalar_t__,char*,char const*) ; 

int inotify_add_watch_and_warn(int fd, const char *pathname, uint32_t mask) {

        if (inotify_add_watch(fd, pathname, mask) < 0) {
                if (errno == ENOSPC)
                        return log_error_errno(errno, "Failed to add a watch for %s: inotify watch limit reached", pathname);

                return log_error_errno(errno, "Failed to add a watch for %s: %m", pathname);
        }

        return 0;
}