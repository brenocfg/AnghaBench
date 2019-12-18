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
 int MS_NODEV ; 
 int MS_NOEXEC ; 
 int MS_NOSUID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  errno ; 
 int log_debug_errno (int,char*,...) ; 
 int /*<<< orphan*/  mkdir_p_label (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mount (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mount_entry_path (int /*<<< orphan*/  const*) ; 
 int path_is_mount_point (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_procfs(const MountEntry *m) {
        int r;

        assert(m);

        (void) mkdir_p_label(mount_entry_path(m), 0755);

        r = path_is_mount_point(mount_entry_path(m), NULL, 0);
        if (r < 0)
                return log_debug_errno(r, "Unable to determine whether /proc is already mounted: %m");
        if (r > 0) /* make this a NOP if /proc is already a mount point */
                return 0;

        /* Mount a new instance, so that we get the one that matches our user namespace, if we are running in one */
        if (mount("proc", mount_entry_path(m), "proc", MS_NOSUID|MS_NOEXEC|MS_NODEV, NULL) < 0)
                return log_debug_errno(errno, "Failed to mount %s: %m", mount_entry_path(m));

        return 1;
}