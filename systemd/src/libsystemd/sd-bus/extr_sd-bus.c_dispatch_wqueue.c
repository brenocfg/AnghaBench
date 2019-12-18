#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
struct TYPE_7__ {int wqueue_size; scalar_t__ windex; int /*<<< orphan*/ * wqueue; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HELLO ; 
 scalar_t__ BUS_MESSAGE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_RUNNING ; 
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_message_unref_queued (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int bus_write_message (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dispatch_wqueue(sd_bus *bus) {
        int r, ret = 0;

        assert(bus);
        assert(IN_SET(bus->state, BUS_RUNNING, BUS_HELLO));

        while (bus->wqueue_size > 0) {

                r = bus_write_message(bus, bus->wqueue[0], &bus->windex);
                if (r < 0)
                        return r;
                else if (r == 0)
                        /* Didn't do anything this time */
                        return ret;
                else if (bus->windex >= BUS_MESSAGE_SIZE(bus->wqueue[0])) {
                        /* Fully written. Let's drop the entry from
                         * the queue.
                         *
                         * This isn't particularly optimized, but
                         * well, this is supposed to be our worst-case
                         * buffer only, and the socket buffer is
                         * supposed to be our primary buffer, and if
                         * it got full, then all bets are off
                         * anyway. */

                        bus->wqueue_size--;
                        bus_message_unref_queued(bus->wqueue[0], bus);
                        memmove(bus->wqueue, bus->wqueue + 1, sizeof(sd_bus_message*) * bus->wqueue_size);
                        bus->windex = 0;

                        ret = 1;
                }
        }

        return ret;
}