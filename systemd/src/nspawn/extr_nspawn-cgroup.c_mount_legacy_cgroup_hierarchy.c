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
 int ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MS_BIND ; 
 int MS_NODEV ; 
 int MS_NOEXEC ; 
 int MS_NOSUID ; 
 int MS_RDONLY ; 
 int MS_REMOUNT ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER_HYBRID ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER_LEGACY ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  mkdir_p (char const*,int) ; 
 int mount_verbose (int /*<<< orphan*/ ,char*,char const*,char const*,int,char const*) ; 
 int path_is_mount_point (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strempty (char const*) ; 
 scalar_t__ streq (char const*,int /*<<< orphan*/ ) ; 
 char* strjoina (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int mount_legacy_cgroup_hierarchy(
                const char *dest,
                const char *controller,
                const char *hierarchy,
                bool read_only) {

        const char *to, *fstype, *opts;
        int r;

        to = strjoina(strempty(dest), "/sys/fs/cgroup/", hierarchy);

        r = path_is_mount_point(to, dest, 0);
        if (r < 0 && r != -ENOENT)
                return log_error_errno(r, "Failed to determine if %s is mounted already: %m", to);
        if (r > 0)
                return 0;

        (void) mkdir_p(to, 0755);

        /* The superblock mount options of the mount point need to be
         * identical to the hosts', and hence writable... */
        if (streq(controller, SYSTEMD_CGROUP_CONTROLLER_HYBRID)) {
                fstype = "cgroup2";
                opts = NULL;
        } else if (streq(controller, SYSTEMD_CGROUP_CONTROLLER_LEGACY)) {
                fstype = "cgroup";
                opts = "none,name=systemd,xattr";
        } else {
                fstype = "cgroup";
                opts = controller;
        }

        r = mount_verbose(LOG_ERR, "cgroup", to, fstype, MS_NOSUID|MS_NOEXEC|MS_NODEV, opts);
        if (r < 0)
                return r;

        /* ... hence let's only make the bind mount read-only, not the superblock. */
        if (read_only) {
                r = mount_verbose(LOG_ERR, NULL, to, NULL,
                                  MS_BIND|MS_REMOUNT|MS_NOSUID|MS_NOEXEC|MS_NODEV|MS_RDONLY, NULL);
                if (r < 0)
                        return r;
        }

        return 1;
}