#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct tm {int dummy; } ;
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {int local_rtc; int /*<<< orphan*/  polkit_registry; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_TIME ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int bus_verify_polkit_async (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clock_get_hwclock (struct tm*) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int clock_set_hwclock (struct tm*) ; 
 int clock_set_timezone (int /*<<< orphan*/ *) ; 
 scalar_t__ clock_settime (int /*<<< orphan*/ ,struct timespec*) ; 
 int context_write_data_local_rtc (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*,char*) ; 
 int /*<<< orphan*/  log_info (char*,char*) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 
 int /*<<< orphan*/  sd_bus_emit_properties_changed (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_error_set_errnof (int /*<<< orphan*/ *,int,char*,char*) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int sd_bus_message_read (TYPE_1__*,char*,int*,int*,int*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timegm (struct tm*) ; 

__attribute__((used)) static int method_set_local_rtc(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        int lrtc, fix_system, interactive;
        Context *c = userdata;
        struct timespec ts;
        int r;

        assert(m);
        assert(c);

        r = sd_bus_message_read(m, "bbb", &lrtc, &fix_system, &interactive);
        if (r < 0)
                return r;

        if (lrtc == c->local_rtc)
                return sd_bus_reply_method_return(m, NULL);

        r = bus_verify_polkit_async(
                        m,
                        CAP_SYS_TIME,
                        "org.freedesktop.timedate1.set-local-rtc",
                        NULL,
                        interactive,
                        UID_INVALID,
                        &c->polkit_registry,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1;

        c->local_rtc = lrtc;

        /* 1. Write new configuration file */
        r = context_write_data_local_rtc(c);
        if (r < 0) {
                log_error_errno(r, "Failed to set RTC to %s: %m", lrtc ? "local" : "UTC");
                return sd_bus_error_set_errnof(error, r, "Failed to set RTC to %s: %m", lrtc ? "local" : "UTC");
        }

        /* 2. Tell the kernel our timezone */
        r = clock_set_timezone(NULL);
        if (r < 0)
                log_debug_errno(r, "Failed to tell kernel about timezone, ignoring: %m");

        /* 3. Synchronize clocks */
        assert_se(clock_gettime(CLOCK_REALTIME, &ts) == 0);

        if (fix_system) {
                struct tm tm;

                /* Sync system clock from RTC; first, initialize the timezone fields of struct tm. */
                if (c->local_rtc)
                        localtime_r(&ts.tv_sec, &tm);
                else
                        gmtime_r(&ts.tv_sec, &tm);

                /* Override the main fields of struct tm, but not the timezone fields */
                r = clock_get_hwclock(&tm);
                if (r < 0)
                        log_debug_errno(r, "Failed to get hardware clock, ignoring: %m");
                else {
                        /* And set the system clock with this */
                        if (c->local_rtc)
                                ts.tv_sec = mktime(&tm);
                        else
                                ts.tv_sec = timegm(&tm);

                        if (clock_settime(CLOCK_REALTIME, &ts) < 0)
                                log_debug_errno(errno, "Failed to update system clock, ignoring: %m");
                }

        } else {
                struct tm tm;

                /* Sync RTC from system clock */
                if (c->local_rtc)
                        localtime_r(&ts.tv_sec, &tm);
                else
                        gmtime_r(&ts.tv_sec, &tm);

                r = clock_set_hwclock(&tm);
                if (r < 0)
                        log_debug_errno(r, "Failed to sync time to hardware clock, ignoring: %m");
        }

        log_info("RTC configured to %s time.", c->local_rtc ? "local" : "UTC");

        (void) sd_bus_emit_properties_changed(sd_bus_message_get_bus(m),
                                              "/org/freedesktop/timedate1", "org.freedesktop.timedate1", "LocalRTC",
                                              NULL);

        return sd_bus_reply_method_return(m, NULL);
}