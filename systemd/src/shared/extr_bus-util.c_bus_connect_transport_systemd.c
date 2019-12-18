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
typedef  int BusTransport ;

/* Variables and functions */
#define  BUS_TRANSPORT_LOCAL 130 
#define  BUS_TRANSPORT_MACHINE 129 
#define  BUS_TRANSPORT_REMOTE 128 
 int /*<<< orphan*/  EHOSTDOWN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int _BUS_TRANSPORT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  assert_return (int,int /*<<< orphan*/ ) ; 
 int bus_connect_system_systemd (int /*<<< orphan*/ **) ; 
 int bus_connect_user_systemd (int /*<<< orphan*/ **) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_booted () ; 
 int sd_bus_open_system_machine (int /*<<< orphan*/ **,char const*) ; 
 int sd_bus_open_system_remote (int /*<<< orphan*/ **,char const*) ; 

int bus_connect_transport_systemd(BusTransport transport, const char *host, bool user, sd_bus **bus) {
        int r;

        assert(transport >= 0);
        assert(transport < _BUS_TRANSPORT_MAX);
        assert(bus);

        assert_return((transport == BUS_TRANSPORT_LOCAL) == !host, -EINVAL);
        assert_return(transport == BUS_TRANSPORT_LOCAL || !user, -EOPNOTSUPP);

        switch (transport) {

        case BUS_TRANSPORT_LOCAL:
                if (user)
                        r = bus_connect_user_systemd(bus);
                else {
                        if (sd_booted() <= 0)
                                /* Print a friendly message when the local system is actually not running systemd as PID 1. */
                                return log_error_errno(SYNTHETIC_ERRNO(EHOSTDOWN),
                                                       "System has not been booted with systemd as init system (PID 1). Can't operate.");
                        r = bus_connect_system_systemd(bus);
                }
                break;

        case BUS_TRANSPORT_REMOTE:
                r = sd_bus_open_system_remote(bus, host);
                break;

        case BUS_TRANSPORT_MACHINE:
                r = sd_bus_open_system_machine(bus, host);
                break;

        default:
                assert_not_reached("Hmm, unknown transport type.");
        }

        return r;
}