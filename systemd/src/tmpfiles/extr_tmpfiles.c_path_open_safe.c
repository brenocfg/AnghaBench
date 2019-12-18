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
 int CHASE_NOFOLLOW ; 
 int CHASE_SAFE ; 
 int CHASE_WARN ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOLINK ; 
 int SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_root ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int chase_symlinks (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  path_is_normalized (char const*) ; 

__attribute__((used)) static int path_open_safe(const char *path) {
        int r, fd;

        /* path_open_safe() returns a file descriptor opened with O_PATH after
         * verifying that the path doesn't contain unsafe transitions, except
         * for its final component as the function does not follow symlink. */

        assert(path);

        if (!path_is_normalized(path))
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Failed to open invalid path '%s'.",
                                       path);

        r = chase_symlinks(path, arg_root, CHASE_SAFE|CHASE_WARN|CHASE_NOFOLLOW, NULL, &fd);
        if (r < 0 && r != -ENOLINK)
                return log_error_errno(r, "Failed to validate path %s: %m", path);

        return r < 0 ? r : fd;
}