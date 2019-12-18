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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_log_create_error (int) ; 
 int log_error_errno (int,char*) ; 
 int sd_bus_get_unique_name (int /*<<< orphan*/ *,char const**) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,char const*) ; 

__attribute__((used)) static int append_controller_property(sd_bus *bus, sd_bus_message *m) {
        const char *unique;
        int r;

        assert(bus);
        assert(m);

        r = sd_bus_get_unique_name(bus, &unique);
        if (r < 0)
                return log_error_errno(r, "Failed to get unique name: %m");

        r = sd_bus_message_append(m, "(sv)", "Controller", "s", unique);
        if (r < 0)
                return bus_log_create_error(r);

        return 0;
}