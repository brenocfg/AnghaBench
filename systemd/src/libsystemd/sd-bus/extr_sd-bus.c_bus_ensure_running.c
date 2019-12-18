#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {scalar_t__ state; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_CLOSED ; 
 int /*<<< orphan*/  BUS_CLOSING ; 
 scalar_t__ BUS_RUNNING ; 
 int /*<<< orphan*/  BUS_UNSET ; 
 int ENOTCONN ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_process (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sd_bus_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 

int bus_ensure_running(sd_bus *bus) {
        int r;

        assert(bus);

        if (IN_SET(bus->state, BUS_UNSET, BUS_CLOSED, BUS_CLOSING))
                return -ENOTCONN;
        if (bus->state == BUS_RUNNING)
                return 1;

        for (;;) {
                r = sd_bus_process(bus, NULL);
                if (r < 0)
                        return r;
                if (bus->state == BUS_RUNNING)
                        return 1;
                if (r > 0)
                        continue;

                r = sd_bus_wait(bus, (uint64_t) -1);
                if (r < 0)
                        return r;
        }
}