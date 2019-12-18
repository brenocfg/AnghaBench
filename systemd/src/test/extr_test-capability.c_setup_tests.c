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
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  NOBODY_USER_NAME ; 
 int /*<<< orphan*/  PR_CAP_AMBIENT ; 
 int /*<<< orphan*/  PR_CAP_AMBIENT_CLEAR_ALL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_gid ; 
 int /*<<< orphan*/  test_uid ; 

__attribute__((used)) static int setup_tests(bool *run_ambient) {
        struct passwd *nobody;
        int r;

        nobody = getpwnam(NOBODY_USER_NAME);
        if (!nobody)
                return log_error_errno(SYNTHETIC_ERRNO(ENOENT), "Could not find nobody user: %m");

        test_uid = nobody->pw_uid;
        test_gid = nobody->pw_gid;

        *run_ambient = false;

        r = prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_CLEAR_ALL, 0, 0, 0);

        /* There's support for PR_CAP_AMBIENT if the prctl() call
         * succeeded or error code was something else than EINVAL. The
         * EINVAL check should be good enough to rule out false
         * positives. */

        if (r >= 0 || errno != EINVAL)
                *run_ambient = true;

        return 0;
}