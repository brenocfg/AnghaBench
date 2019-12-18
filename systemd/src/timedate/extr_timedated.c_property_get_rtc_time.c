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
typedef  int usec_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int USEC_PER_SEC ; 
 int clock_get_hwclock (struct tm*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_warning (char*) ; 
 int sd_bus_error_set_errnof (int /*<<< orphan*/ *,int,char*) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ timegm (struct tm*) ; 

__attribute__((used)) static int property_get_rtc_time(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        struct tm tm = {};
        usec_t t = 0;
        int r;

        r = clock_get_hwclock(&tm);
        if (r == -EBUSY)
                log_warning("/dev/rtc is busy. Is somebody keeping it open continuously? That's not a good idea... Returning a bogus RTC timestamp.");
        else if (r == -ENOENT)
                log_debug("/dev/rtc not found.");
        else if (r < 0)
                return sd_bus_error_set_errnof(error, r, "Failed to read RTC: %m");
        else
                t = (usec_t) timegm(&tm) * USEC_PER_SEC;

        return sd_bus_message_append(reply, "t", t);
}