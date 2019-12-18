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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char**) ; 
 int /*<<< orphan*/  sd_bus_get_event (int /*<<< orphan*/ ) ; 
 int sd_bus_get_property_string (int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int match_startup_finished(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        char **state = userdata;
        int r;

        assert(state);

        r = sd_bus_get_property_string(
                        sd_bus_message_get_bus(m),
                        "org.freedesktop.systemd1",
                        "/org/freedesktop/systemd1",
                        "org.freedesktop.systemd1.Manager",
                        "SystemState",
                        NULL,
                        state);

        sd_event_exit(sd_bus_get_event(sd_bus_message_get_bus(m)), r);
        return 0;
}