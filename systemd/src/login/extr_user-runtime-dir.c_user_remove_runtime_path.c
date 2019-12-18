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
 int /*<<< orphan*/  EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MNT_DETACH ; 
 int /*<<< orphan*/  REMOVE_ROOT ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 int /*<<< orphan*/  log_debug_errno (int,char*,char const*) ; 
 int log_error_errno (int,char*,char const*) ; 
 char const* path_is_absolute (char const*) ; 
 int rm_rf (char const*,int /*<<< orphan*/ ) ; 
 int umount2 (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int user_remove_runtime_path(const char *runtime_path) {
        int r;

        assert(runtime_path);
        assert(path_is_absolute(runtime_path));

        r = rm_rf(runtime_path, 0);
        if (r < 0)
                log_debug_errno(r, "Failed to remove runtime directory %s (before unmounting), ignoring: %m", runtime_path);

        /* Ignore cases where the directory isn't mounted, as that's quite possible, if we lacked the permissions to
         * mount something */
        r = umount2(runtime_path, MNT_DETACH);
        if (r < 0 && !IN_SET(errno, EINVAL, ENOENT))
                log_debug_errno(errno, "Failed to unmount user runtime directory %s, ignoring: %m", runtime_path);

        r = rm_rf(runtime_path, REMOVE_ROOT);
        if (r < 0 && r != -ENOENT)
                return log_error_errno(r, "Failed to remove runtime directory %s (after unmounting): %m", runtime_path);

        return 0;
}