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
 int /*<<< orphan*/  EHOSTDOWN ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_FILE_SYSTEM ; 
 int /*<<< orphan*/  arg_host ; 
 scalar_t__ arg_scope ; 
 int /*<<< orphan*/  arg_transport ; 
 int bus_connect_transport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int bus_connect_transport_systemd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int acquire_bus(sd_bus **bus, bool *use_full_bus) {
        bool user = arg_scope != UNIT_FILE_SYSTEM;
        int r;

        if (use_full_bus && *use_full_bus) {
                r = bus_connect_transport(arg_transport, arg_host, user, bus);
                if (IN_SET(r, 0, -EHOSTDOWN))
                        return r;

                *use_full_bus = false;
        }

        return bus_connect_transport_systemd(arg_transport, arg_host, user, bus);
}