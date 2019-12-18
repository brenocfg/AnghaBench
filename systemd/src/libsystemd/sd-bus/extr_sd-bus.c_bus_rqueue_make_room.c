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
struct TYPE_4__ {scalar_t__ rqueue_size; int /*<<< orphan*/  rqueue_allocated; int /*<<< orphan*/  rqueue; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 scalar_t__ BUS_RQUEUE_MAX ; 
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GREEDY_REALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

int bus_rqueue_make_room(sd_bus *bus) {
        assert(bus);

        if (bus->rqueue_size >= BUS_RQUEUE_MAX)
                return -ENOBUFS;

        if (!GREEDY_REALLOC(bus->rqueue, bus->rqueue_allocated, bus->rqueue_size + 1))
                return -ENOMEM;

        return 0;
}