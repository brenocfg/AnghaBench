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
 int ENOTTY ; 
 int btrfs_subvol_auto_qgroup (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,...) ; 
 int log_error_errno (int,char*,...) ; 
 int /*<<< orphan*/  log_info (char*) ; 

int import_assign_pool_quota_and_warn(const char *path) {
        int r;

        r = btrfs_subvol_auto_qgroup("/var/lib/machines", 0, true);
        if (r == -ENOTTY)  {
                log_debug_errno(r, "Failed to set up default quota hierarchy for /var/lib/machines, as directory is not on btrfs or not a subvolume. Ignoring.");
                return 0;
        }
        if (r < 0)
                return log_error_errno(r, "Failed to set up default quota hierarchy for /var/lib/machines: %m");
        if (r > 0)
                log_info("Set up default quota hierarchy for /var/lib/machines.");

        r = btrfs_subvol_auto_qgroup(path, 0, true);
        if (r == -ENOTTY) {
                log_debug_errno(r, "Failed to set up quota hierarchy for %s, as directory is not on btrfs or not a subvolume. Ignoring.", path);
                return 0;
        }
        if (r < 0)
                return log_error_errno(r, "Failed to set up default quota hierarchy for %s: %m", path);
        if (r > 0)
                log_debug("Set up default quota hierarchy for %s.", path);

        return 0;
}