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
 int /*<<< orphan*/  ACTION_HALT ; 
 int /*<<< orphan*/  ACTION_POWEROFF ; 
 int /*<<< orphan*/  ACTION_REBOOT ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  arg_action ; 
 scalar_t__ arg_dry_run ; 
 scalar_t__ arg_force ; 
 int arg_no_block ; 
 int /*<<< orphan*/  arg_no_wtmp ; 
 scalar_t__ arg_when ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ geteuid () ; 
 int halt_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int logind_check_inhibitors (int /*<<< orphan*/ ) ; 
 int logind_reboot (int /*<<< orphan*/ ) ; 
 scalar_t__ logind_schedule_shutdown () ; 
 int /*<<< orphan*/  must_be_root () ; 
 scalar_t__ sd_booted () ; 
 int start_with_fallback () ; 
 int utmp_put_shutdown () ; 

__attribute__((used)) static int halt_main(void) {
        int r;

        r = logind_check_inhibitors(arg_action);
        if (r < 0)
                return r;

        /* Delayed shutdown requested, and was successful */
        if (arg_when > 0 && logind_schedule_shutdown() == 0)
                return 0;
        /* no delay, or logind failed or is not at all available */

        if (geteuid() != 0) {
                if (arg_dry_run || arg_force > 0) {
                        (void) must_be_root();
                        return -EPERM;
                }

                /* Try logind if we are a normal user and no special
                 * mode applies. Maybe polkit allows us to shutdown
                 * the machine. */
                if (IN_SET(arg_action, ACTION_POWEROFF, ACTION_REBOOT, ACTION_HALT)) {
                        r = logind_reboot(arg_action);
                        if (r >= 0)
                                return r;
                        if (IN_SET(r, -EOPNOTSUPP, -EINPROGRESS))
                                /* requested operation is not
                                 * supported on the local system or
                                 * already in progress */
                                return r;
                        /* on all other errors, try low-level operation */
                }
        }

        /* In order to minimize the difference between operation with and
         * without logind, we explicitly enable non-blocking mode for this,
         * as logind's shutdown operations are always non-blocking. */
        arg_no_block = true;

        if (!arg_dry_run && !arg_force)
                return start_with_fallback();

        assert(geteuid() == 0);

        if (!arg_no_wtmp) {
                if (sd_booted() > 0)
                        log_debug("Not writing utmp record, assuming that systemd-update-utmp is used.");
                else {
                        r = utmp_put_shutdown();
                        if (r < 0)
                                log_warning_errno(r, "Failed to write utmp record: %m");
                }
        }

        if (arg_dry_run)
                return 0;

        r = halt_now(arg_action);
        return log_error_errno(r, "Failed to reboot: %m");
}