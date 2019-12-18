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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  bus; } ;
typedef  TYPE_1__ BusWaitForUnits ;

/* Variables and functions */
 scalar_t__ BUS_WAIT_RUNNING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_process (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_bus_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bus_wait_for_units_run(BusWaitForUnits *d) {
        int r;

        assert(d);

        while (d->state == BUS_WAIT_RUNNING) {

                r = sd_bus_process(d->bus, NULL);
                if (r < 0)
                        return r;
                if (r > 0)
                        continue;

                r = sd_bus_wait(d->bus, (uint64_t) -1);
                if (r < 0)
                        return r;
        }

        return d->state;
}