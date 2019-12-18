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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int EBADE ; 
 int EOPNOTSUPP ; 
 scalar_t__ USER_NAMESPACE_NO ; 
 int /*<<< orphan*/  arg_uid_range ; 
 int /*<<< orphan*/  arg_uid_shift ; 
 int /*<<< orphan*/  arg_userns_chown ; 
 scalar_t__ arg_userns_mode ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int log_error_errno (int,char*) ; 
 int path_patch_uid (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recursive_chown(const char *directory, uid_t shift, uid_t range) {
        int r;

        assert(directory);

        if (arg_userns_mode == USER_NAMESPACE_NO || !arg_userns_chown)
                return 0;

        r = path_patch_uid(directory, arg_uid_shift, arg_uid_range);
        if (r == -EOPNOTSUPP)
                return log_error_errno(r, "Automatic UID/GID adjusting is only supported for UID/GID ranges starting at multiples of 2^16 with a range of 2^16.");
        if (r == -EBADE)
                return log_error_errno(r, "Upper 16 bits of root directory UID and GID do not match.");
        if (r < 0)
                return log_error_errno(r, "Failed to adjust UID/GID shift of OS tree: %m");
        if (r == 0)
                log_debug("Root directory of image is already owned by the right UID/GID range, skipping recursive chown operation.");
        else
                log_debug("Patched directory tree to match UID/GID range.");

        return r;
}