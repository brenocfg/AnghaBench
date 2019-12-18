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
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  EPERM ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fd_fdinfo_mnt_id (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*) ; 
 int name_to_handle_at_loop (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

int path_get_mnt_id(const char *path, int *ret) {
        int r;

        r = name_to_handle_at_loop(AT_FDCWD, path, NULL, ret, 0);
        if (IN_SET(r, -EOPNOTSUPP, -ENOSYS, -EACCES, -EPERM, -EOVERFLOW, -EINVAL)) /* kernel/fs don't support this, or seccomp blocks access, or untriggered mount, or name_to_handle_at() is flaky */
                return fd_fdinfo_mnt_id(AT_FDCWD, path, 0, ret);

        return r;
}