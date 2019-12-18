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
struct TYPE_6__ {int /*<<< orphan*/  machine_units; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  Machine ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_log_parse_error (int) ; 
 int /*<<< orphan*/ * hashmap_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  machine_add_to_gc_queue (int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (TYPE_1__*,char*,char const**,char const**) ; 

int match_unit_removed(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        const char *path, *unit;
        Manager *m = userdata;
        Machine *machine;
        int r;

        assert(message);
        assert(m);

        r = sd_bus_message_read(message, "so", &unit, &path);
        if (r < 0) {
                bus_log_parse_error(r);
                return 0;
        }

        machine = hashmap_get(m->machine_units, unit);
        if (!machine)
                return 0;

        machine_add_to_gc_queue(machine);
        return 0;
}