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
 int clock_apply_epoch () ; 
 scalar_t__ clock_is_localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_reset_timewarp () ; 
 int clock_set_timezone (int*) ; 
 int /*<<< orphan*/  in_initrd () ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,...) ; 

__attribute__((used)) static void initialize_clock(void) {
        int r;

        if (clock_is_localtime(NULL) > 0) {
                int min;

                /*
                 * The very first call of settimeofday() also does a time warp in the kernel.
                 *
                 * In the rtc-in-local time mode, we set the kernel's timezone, and rely on external tools to take care
                 * of maintaining the RTC and do all adjustments.  This matches the behavior of Windows, which leaves
                 * the RTC alone if the registry tells that the RTC runs in UTC.
                 */
                r = clock_set_timezone(&min);
                if (r < 0)
                        log_error_errno(r, "Failed to apply local time delta, ignoring: %m");
                else
                        log_info("RTC configured in localtime, applying delta of %i minutes to system time.", min);

        } else if (!in_initrd()) {
                /*
                 * Do a dummy very first call to seal the kernel's time warp magic.
                 *
                 * Do not call this from inside the initrd. The initrd might not carry /etc/adjtime with LOCAL, but the
                 * real system could be set up that way. In such case, we need to delay the time-warp or the sealing
                 * until we reach the real system.
                 *
                 * Do no set the kernel's timezone. The concept of local time cannot be supported reliably, the time
                 * will jump or be incorrect at every daylight saving time change. All kernel local time concepts will
                 * be treated as UTC that way.
                 */
                (void) clock_reset_timewarp();
        }

        r = clock_apply_epoch();
        if (r < 0)
                log_error_errno(r, "Current system time is before build time, but cannot correct: %m");
        else if (r > 0)
                log_info("System time before build time, advancing clock.");
}