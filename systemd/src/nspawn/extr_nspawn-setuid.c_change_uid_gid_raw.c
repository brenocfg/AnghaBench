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
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fchown (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gid_is_valid (scalar_t__) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setgroups (size_t,scalar_t__ const*) ; 
 scalar_t__ setresgid (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ setresuid (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uid_is_valid (scalar_t__) ; 

int change_uid_gid_raw(
                uid_t uid,
                gid_t gid,
                const gid_t *supplementary_gids,
                size_t n_supplementary_gids) {

        if (!uid_is_valid(uid))
                uid = 0;
        if (!gid_is_valid(gid))
                gid = 0;

        (void) fchown(STDIN_FILENO, uid, gid);
        (void) fchown(STDOUT_FILENO, uid, gid);
        (void) fchown(STDERR_FILENO, uid, gid);

        if (setgroups(n_supplementary_gids, supplementary_gids) < 0)
                return log_error_errno(errno, "Failed to set auxiliary groups: %m");

        if (setresgid(gid, gid, gid) < 0)
                return log_error_errno(errno, "setresgid() failed: %m");

        if (setresuid(uid, uid, uid) < 0)
                return log_error_errno(errno, "setresuid() failed: %m");

        return 0;
}