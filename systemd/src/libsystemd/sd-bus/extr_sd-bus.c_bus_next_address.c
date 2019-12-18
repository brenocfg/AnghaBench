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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_reset_parsed_address (int /*<<< orphan*/ *) ; 
 int bus_start_address (int /*<<< orphan*/ *) ; 

int bus_next_address(sd_bus *b) {
        assert(b);

        bus_reset_parsed_address(b);
        return bus_start_address(b);
}