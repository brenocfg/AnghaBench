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
 int /*<<< orphan*/  arg_all ; 
 int /*<<< orphan*/  arg_property ; 
 int /*<<< orphan*/  arg_value ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_log_parse_error (int) ; 
 int bus_print_all_properties (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int show_properties(int argc, char **argv, void *userdata) {
        sd_bus *bus = userdata;
        int r;

        assert(bus);

        r = bus_print_all_properties(bus,
                                     "org.freedesktop.timedate1",
                                     "/org/freedesktop/timedate1",
                                     NULL,
                                     arg_property,
                                     arg_value,
                                     arg_all,
                                     NULL);
        if (r < 0)
                return bus_log_parse_error(r);

        return 0;
}