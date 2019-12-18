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
typedef  int /*<<< orphan*/  UnitType ;

/* Variables and functions */
 scalar_t__ arg_aggressive_gc ; 
 char* arg_description ; 
 int bus_append_unit_property_assignment_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int bus_log_create_error (int) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 

__attribute__((used)) static int transient_unit_set_properties(sd_bus_message *m, UnitType t, char **properties) {
        int r;

        r = sd_bus_message_append(m, "(sv)", "Description", "s", arg_description);
        if (r < 0)
                return bus_log_create_error(r);

        if (arg_aggressive_gc) {
                r = sd_bus_message_append(m, "(sv)", "CollectMode", "s", "inactive-or-failed");
                if (r < 0)
                        return bus_log_create_error(r);
        }

        r = bus_append_unit_property_assignment_many(m, t, properties);
        if (r < 0)
                return r;

        return 0;
}