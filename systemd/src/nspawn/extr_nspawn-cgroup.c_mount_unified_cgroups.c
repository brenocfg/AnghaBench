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
 int /*<<< orphan*/  EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MS_NODEV ; 
 int MS_NOEXEC ; 
 int MS_NOSUID ; 
 int SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  mkdir_p (char const*,int) ; 
 int mount_verbose (int /*<<< orphan*/ ,char*,char const*,char*,int,int /*<<< orphan*/ *) ; 
 int path_is_mount_point (char const*,char const*,int /*<<< orphan*/ ) ; 
 char* prefix_roota (char const*,char*) ; 

__attribute__((used)) static int mount_unified_cgroups(const char *dest) {
        const char *p;
        int r;

        assert(dest);

        p = prefix_roota(dest, "/sys/fs/cgroup");

        (void) mkdir_p(p, 0755);

        r = path_is_mount_point(p, dest, AT_SYMLINK_FOLLOW);
        if (r < 0)
                return log_error_errno(r, "Failed to determine if %s is mounted already: %m", p);
        if (r > 0) {
                p = prefix_roota(dest, "/sys/fs/cgroup/cgroup.procs");
                if (access(p, F_OK) >= 0)
                        return 0;
                if (errno != ENOENT)
                        return log_error_errno(errno, "Failed to determine if mount point %s contains the unified cgroup hierarchy: %m", p);

                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "%s is already mounted but not a unified cgroup hierarchy. Refusing.", p);
        }

        return mount_verbose(LOG_ERR, "cgroup", p, "cgroup2", MS_NOSUID|MS_NOEXEC|MS_NODEV, NULL);
}