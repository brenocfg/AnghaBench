#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  private_buses; int /*<<< orphan*/ * system_bus; int /*<<< orphan*/ * api_bus; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_done_api (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_done_system (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy_bus (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/ * sd_bus_message_get_bus (TYPE_1__*) ; 
 scalar_t__ set_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int signal_disconnected(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        sd_bus *bus;

        assert(message);
        assert(m);
        assert_se(bus = sd_bus_message_get_bus(message));

        if (bus == m->api_bus)
                bus_done_api(m);
        if (bus == m->system_bus)
                bus_done_system(m);

        if (set_remove(m->private_buses, bus)) {
                log_debug("Got disconnect on private connection.");
                destroy_bus(m, &bus);
        }

        return 0;
}