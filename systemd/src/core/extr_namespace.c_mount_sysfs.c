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
typedef  int /*<<< orphan*/  MountEntry ;

/* Variables and functions */
 int MS_BIND ; 
 int MS_REC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  errno ; 
 int log_debug_errno (int,char*,...) ; 
 int /*<<< orphan*/  mkdir_p_label (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mount (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mount_entry_path (int /*<<< orphan*/  const*) ; 
 int path_is_mount_point (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_sysfs(const MountEntry *m) {
        int r;

        assert(m);

        (void) mkdir_p_label(mount_entry_path(m), 0755);

        r = path_is_mount_point(mount_entry_path(m), NULL, 0);
        if (r < 0)
                return log_debug_errno(r, "Unable to determine whether /sys is already mounted: %m");
        if (r > 0) /* make this a NOP if /sys is already a mount point */
                return 0;

        /* Bind mount the host's version so that we get all child mounts of it, too. */
        if (mount("/sys", mount_entry_path(m), NULL, MS_BIND|MS_REC, NULL) < 0)
                return log_debug_errno(errno, "Failed to mount %s: %m", mount_entry_path(m));

        return 1;
}