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
typedef  size_t BusFocus ;

/* Variables and functions */
 size_t BUS_FULL ; 
 size_t BUS_MANAGER ; 
 scalar_t__ BUS_TRANSPORT_LOCAL ; 
 scalar_t__ UNIT_FILE_SYSTEM ; 
 size_t _BUS_FOCUS_MAX ; 
 int /*<<< orphan*/  arg_ask_password ; 
 int /*<<< orphan*/  arg_host ; 
 scalar_t__ arg_scope ; 
 scalar_t__ arg_transport ; 
 int /*<<< orphan*/  assert (int) ; 
 int bus_connect_transport (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int bus_connect_transport_systemd (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** buses ; 
 scalar_t__ getenv_bool (char*) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  sd_bus_set_allow_interactive_authorization (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acquire_bus(BusFocus focus, sd_bus **ret) {
        int r;

        assert(focus < _BUS_FOCUS_MAX);
        assert(ret);

        /* We only go directly to the manager, if we are using a local transport */
        if (arg_transport != BUS_TRANSPORT_LOCAL)
                focus = BUS_FULL;

        if (getenv_bool("SYSTEMCTL_FORCE_BUS") > 0)
                focus = BUS_FULL;

        if (!buses[focus]) {
                bool user;

                user = arg_scope != UNIT_FILE_SYSTEM;

                if (focus == BUS_MANAGER)
                        r = bus_connect_transport_systemd(arg_transport, arg_host, user, &buses[focus]);
                else
                        r = bus_connect_transport(arg_transport, arg_host, user, &buses[focus]);
                if (r < 0)
                        return log_error_errno(r, "Failed to connect to bus: %m");

                (void) sd_bus_set_allow_interactive_authorization(buses[focus], arg_ask_password);
        }

        *ret = buses[focus];
        return 0;
}