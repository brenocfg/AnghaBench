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
 char const* DEFAULT_SYSTEM_BUS_ADDRESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_set_address (int /*<<< orphan*/ *,char const*) ; 
 char* secure_getenv (char*) ; 

int bus_set_address_system(sd_bus *b) {
        const char *e;
        assert(b);

        e = secure_getenv("DBUS_SYSTEM_BUS_ADDRESS");
        if (e)
                return sd_bus_set_address(b, e);

        return sd_bus_set_address(b, DEFAULT_SYSTEM_BUS_ADDRESS);
}