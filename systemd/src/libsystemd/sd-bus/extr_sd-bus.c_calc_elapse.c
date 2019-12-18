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
typedef  scalar_t__ usec_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_AUTHENTICATING ; 
 int /*<<< orphan*/  BUS_OPENING ; 
 int /*<<< orphan*/  BUS_WATCH_BIND ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 

__attribute__((used)) static usec_t calc_elapse(sd_bus *bus, uint64_t usec) {
        assert(bus);

        if (usec == (uint64_t) -1)
                return 0;

        /* We start all timeouts the instant we enter BUS_HELLO/BUS_RUNNING state, so that the don't run in parallel
         * with any connection setup states. Hence, if a method callback is started earlier than that we just store the
         * relative timestamp, and afterwards the absolute one. */

        if (IN_SET(bus->state, BUS_WATCH_BIND, BUS_OPENING, BUS_AUTHENTICATING))
                return usec;
        else
                return now(CLOCK_MONOTONIC) + usec;
}