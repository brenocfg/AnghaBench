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
 scalar_t__ MANAGER_IS_USER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 
 int sd_bus_match_signal_async (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_agent_released ; 

__attribute__((used)) static int bus_setup_system(Manager *m, sd_bus *bus) {
        int r;

        assert(m);
        assert(bus);

        /* if we are a user instance we get the Released message via the system bus */
        if (MANAGER_IS_USER(m)) {
                r = sd_bus_match_signal_async(
                                bus,
                                NULL,
                                NULL,
                                "/org/freedesktop/systemd1/agent",
                                "org.freedesktop.systemd1.Agent",
                                "Released",
                                signal_agent_released, NULL, m);
                if (r < 0)
                        log_warning_errno(r, "Failed to request Released match on system bus: %m");
        }

        log_debug("Successfully connected to system bus.");
        return 0;
}