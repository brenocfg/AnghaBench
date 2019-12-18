#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_5__ {int /*<<< orphan*/  create_message; } ;
typedef  int /*<<< orphan*/  Manager ;
typedef  TYPE_1__ Machine ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  machine_add_to_gc_queue (TYPE_1__*) ; 
 int machine_start (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int method_create_or_register_machine (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,char,char*) ; 
 int /*<<< orphan*/  sd_bus_message_ref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_create_machine_internal(sd_bus_message *message, bool read_network, void *userdata, sd_bus_error *error) {
        Manager *manager = userdata;
        Machine *m = NULL;
        int r;

        assert(message);
        assert(manager);

        r = method_create_or_register_machine(manager, message, read_network, &m, error);
        if (r < 0)
                return r;

        r = sd_bus_message_enter_container(message, 'a', "(sv)");
        if (r < 0)
                goto fail;

        r = machine_start(m, message, error);
        if (r < 0)
                goto fail;

        m->create_message = sd_bus_message_ref(message);
        return 1;

fail:
        machine_add_to_gc_queue(m);
        return r;
}