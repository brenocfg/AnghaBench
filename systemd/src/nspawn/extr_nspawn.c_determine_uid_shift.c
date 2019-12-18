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
typedef  int uid_t ;
struct stat {int st_uid; int st_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int UID_INVALID ; 
 int UINT32_C (int) ; 
 scalar_t__ USER_NAMESPACE_NO ; 
 int arg_uid_range ; 
 int arg_uid_shift ; 
 scalar_t__ arg_userns_mode ; 
 int /*<<< orphan*/  errno ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,...) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int determine_uid_shift(const char *directory) {
        int r;

        if (arg_userns_mode == USER_NAMESPACE_NO) {
                arg_uid_shift = 0;
                return 0;
        }

        if (arg_uid_shift == UID_INVALID) {
                struct stat st;

                r = stat(directory, &st);
                if (r < 0)
                        return log_error_errno(errno, "Failed to determine UID base of %s: %m", directory);

                arg_uid_shift = st.st_uid & UINT32_C(0xffff0000);

                if (arg_uid_shift != (st.st_gid & UINT32_C(0xffff0000)))
                        return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "UID and GID base of %s don't match.", directory);

                arg_uid_range = UINT32_C(0x10000);
        }

        if (arg_uid_shift > (uid_t) -1 - arg_uid_range)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "UID base too high for UID range.");

        return 0;
}