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
 int /*<<< orphan*/  AT_SYMLINK_FOLLOW ; 
 int ENOENT ; 
 int dir_is_empty (char const*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int log_warning_errno (int,char*,char const*) ; 
 int path_is_mount_point (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int path_is_busy(const char *where) {
        int r;

        /* already a mountpoint; generators run during reload */
        r = path_is_mount_point(where, NULL, AT_SYMLINK_FOLLOW);
        if (r > 0)
                return false;

        /* the directory might not exist on a stateless system */
        if (r == -ENOENT)
                return false;

        if (r < 0)
                return log_warning_errno(r, "Cannot check if \"%s\" is a mount point: %m", where);

        /* not a mountpoint but it contains files */
        r = dir_is_empty(where);
        if (r < 0)
                return log_warning_errno(r, "Cannot check if \"%s\" is empty: %m", where);
        if (r > 0)
                return false;

        log_debug("\"%s\" already populated, ignoring.", where);
        return true;
}