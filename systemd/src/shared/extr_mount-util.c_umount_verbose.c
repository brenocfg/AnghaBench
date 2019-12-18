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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ umount (char const*) ; 

int umount_verbose(const char *what) {
        log_debug("Umounting %s...", what);
        if (umount(what) < 0)
                return log_error_errno(errno, "Failed to unmount %s: %m", what);
        return 0;
}