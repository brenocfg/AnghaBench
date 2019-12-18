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
typedef  int /*<<< orphan*/  sd_bus ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int log_error_errno (int,char*) ; 
 int sd_bus_match_signal_async (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_disconnected ; 

__attribute__((used)) static int bus_setup_disconnected_match(Manager *m, sd_bus *bus) {
        int r;

        assert(m);
        assert(bus);

        r = sd_bus_match_signal_async(
                        bus,
                        NULL,
                        "org.freedesktop.DBus.Local",
                        "/org/freedesktop/DBus/Local",
                        "org.freedesktop.DBus.Local",
                        "Disconnected",
                        signal_disconnected, NULL, m);
        if (r < 0)
                return log_error_errno(r, "Failed to request match for Disconnected message: %m");

        return 0;
}