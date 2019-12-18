#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  dynamic_hostname; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 int log_error_errno (int,char*) ; 
 int log_oom () ; 
 int sd_bus_call_method_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,TYPE_1__*,char*,char const*,int) ; 
 scalar_t__ sd_bus_is_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hostname_handler ; 
 int /*<<< orphan*/  strna (char const*) ; 

int manager_set_hostname(Manager *m, const char *hostname) {
        int r;

        log_debug("Setting transient hostname: '%s'", strna(hostname));

        if (free_and_strdup(&m->dynamic_hostname, hostname) < 0)
                return log_oom();

        if (!m->bus || sd_bus_is_ready(m->bus) <= 0) {
                log_debug("Not connected to system bus, setting hostname later.");
                return 0;
        }

        r = sd_bus_call_method_async(
                        m->bus,
                        NULL,
                        "org.freedesktop.hostname1",
                        "/org/freedesktop/hostname1",
                        "org.freedesktop.hostname1",
                        "SetHostname",
                        set_hostname_handler,
                        m,
                        "sb",
                        hostname,
                        false);

        if (r < 0)
                return log_error_errno(r, "Could not set transient hostname: %m");

        return 0;
}