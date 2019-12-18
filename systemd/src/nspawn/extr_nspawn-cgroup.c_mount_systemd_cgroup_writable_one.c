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
 int /*<<< orphan*/  LOG_ERR ; 
 int MS_BIND ; 
 int MS_NODEV ; 
 int MS_NOEXEC ; 
 int MS_NOSUID ; 
 int MS_RDONLY ; 
 int MS_REMOUNT ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int mount_verbose (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mount_systemd_cgroup_writable_one(const char *root, const char *own) {
        int r;

        assert(root);
        assert(own);

        /* Make our own cgroup a (writable) bind mount */
        r = mount_verbose(LOG_ERR, own, own, NULL, MS_BIND, NULL);
        if (r < 0)
                return r;

        /* And then remount the systemd cgroup root read-only */
        return mount_verbose(LOG_ERR, NULL, root, NULL,
                             MS_BIND|MS_REMOUNT|MS_NOSUID|MS_NOEXEC|MS_NODEV|MS_RDONLY, NULL);
}