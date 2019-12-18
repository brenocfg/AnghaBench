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
typedef  char const* usec_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 scalar_t__ STR_IN_SET (char const*,char*,char*,...) ; 
 int bus_append_parse_boolean (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_append_parse_sec_rename (int /*<<< orphan*/ *,char const*,char const*) ; 
 int bus_log_create_error (int) ; 
 scalar_t__ isempty (char const*) ; 
 int log_error_errno (int,char*,char const*,char const*) ; 
 int parse_sec (char const*,char const**) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,int,...) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int bus_append_timer_property(sd_bus_message *m, const char *field, const char *eq) {
        int r;

        if (STR_IN_SET(field, "WakeSystem", "RemainAfterElapse", "Persistent",
                       "OnTimezoneChange", "OnClockChange"))
                return bus_append_parse_boolean(m, field, eq);

        if (STR_IN_SET(field, "AccuracySec", "RandomizedDelaySec"))
                return bus_append_parse_sec_rename(m, field, eq);

        if (STR_IN_SET(field,
                       "OnActiveSec", "OnBootSec", "OnStartupSec",
                       "OnUnitActiveSec","OnUnitInactiveSec")) {
                if (isempty(eq))
                        r = sd_bus_message_append(m, "(sv)", "TimersMonotonic", "a(st)", 0);
                else {
                        usec_t t;
                        r = parse_sec(eq, &t);
                        if (r < 0)
                                return log_error_errno(r, "Failed to parse %s=%s: %m", field, eq);

                        r = sd_bus_message_append(m, "(sv)", "TimersMonotonic", "a(st)", 1, field, t);
                }
                if (r < 0)
                        return bus_log_create_error(r);

                return 1;
        }

        if (streq(field, "OnCalendar")) {
                if (isempty(eq))
                        r = sd_bus_message_append(m, "(sv)", "TimersCalendar", "a(ss)", 0);
                else
                        r = sd_bus_message_append(m, "(sv)", "TimersCalendar", "a(ss)", 1, field, eq);
                if (r < 0)
                        return bus_log_create_error(r);

                return 1;
        }

        return 0;
}