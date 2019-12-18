#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {struct TYPE_21__* current_message; int /*<<< orphan*/  iteration_counter; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_process_object (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug_bus_message (TYPE_1__*) ; 
 int process_builtin (TYPE_1__*,TYPE_1__*) ; 
 int process_fd_check (TYPE_1__*,TYPE_1__*) ; 
 int process_filter (TYPE_1__*,TYPE_1__*) ; 
 int process_hello (TYPE_1__*,TYPE_1__*) ; 
 int process_match (TYPE_1__*,TYPE_1__*) ; 
 int process_reply (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int process_message(sd_bus *bus, sd_bus_message *m) {
        int r;

        assert(bus);
        assert(m);

        bus->current_message = m;
        bus->iteration_counter++;

        log_debug_bus_message(m);

        r = process_hello(bus, m);
        if (r != 0)
                goto finish;

        r = process_reply(bus, m);
        if (r != 0)
                goto finish;

        r = process_fd_check(bus, m);
        if (r != 0)
                goto finish;

        r = process_filter(bus, m);
        if (r != 0)
                goto finish;

        r = process_match(bus, m);
        if (r != 0)
                goto finish;

        r = process_builtin(bus, m);
        if (r != 0)
                goto finish;

        r = bus_process_object(bus, m);

finish:
        bus->current_message = NULL;
        return r;
}