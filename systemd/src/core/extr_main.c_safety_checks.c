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
 scalar_t__ ACTION_RUN ; 
 scalar_t__ ACTION_TEST ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  EUNATCH ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ arg_action ; 
 scalar_t__ arg_system ; 
 int /*<<< orphan*/  getenv (char*) ; 
 scalar_t__ geteuid () ; 
 int getpid_cached () ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ running_in_chroot () ; 
 scalar_t__ sd_booted () ; 

__attribute__((used)) static int safety_checks(void) {

        if (getpid_cached() == 1 &&
            arg_action != ACTION_RUN)
                return log_error_errno(SYNTHETIC_ERRNO(EPERM),
                                       "Unsupported execution mode while PID 1.");

        if (getpid_cached() == 1 &&
            !arg_system)
                return log_error_errno(SYNTHETIC_ERRNO(EPERM),
                                       "Can't run --user mode as PID 1.");

        if (arg_action == ACTION_RUN &&
            arg_system &&
            getpid_cached() != 1)
                return log_error_errno(SYNTHETIC_ERRNO(EPERM),
                                       "Can't run system mode unless PID 1.");

        if (arg_action == ACTION_TEST &&
            geteuid() == 0)
                return log_error_errno(SYNTHETIC_ERRNO(EPERM),
                                       "Don't run test mode as root.");

        if (!arg_system &&
            arg_action == ACTION_RUN &&
            sd_booted() <= 0)
                return log_error_errno(SYNTHETIC_ERRNO(EOPNOTSUPP),
                                       "Trying to run as user instance, but the system has not been booted with systemd.");

        if (!arg_system &&
            arg_action == ACTION_RUN &&
            !getenv("XDG_RUNTIME_DIR"))
                return log_error_errno(SYNTHETIC_ERRNO(EUNATCH),
                                       "Trying to run as user instance, but $XDG_RUNTIME_DIR is not set.");

        if (arg_system &&
            arg_action == ACTION_RUN &&
            running_in_chroot() > 0)
                return log_error_errno(SYNTHETIC_ERRNO(EOPNOTSUPP),
                                       "Cannot be run in a chroot() environment.");

        return 0;
}