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

/* Variables and functions */
 int /*<<< orphan*/  arg_ask_password ; 
 int /*<<< orphan*/  arg_host ; 
 int /*<<< orphan*/  arg_transport ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int bus_connect_transport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  sd_bus_set_allow_interactive_authorization (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acquire_bus(sd_bus **bus) {
        int r;

        assert(bus);

        if (*bus)
                return 0;

        r = bus_connect_transport(arg_transport, arg_host, false, bus);
        if (r < 0)
                return log_error_errno(r, "Failed to connect to bus: %m");

        (void) sd_bus_set_allow_interactive_authorization(*bus, arg_ask_password);

        return 0;
}