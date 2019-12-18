#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  userdata; int /*<<< orphan*/  (* ready_callback ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ BusWaitForUnits ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_wait_for_units_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  sd_bus_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_message_get_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_disconnected(sd_bus_message *m, void *userdata, sd_bus_error *error) {
        BusWaitForUnits *d = userdata;

        assert(m);
        assert(d);

        log_error("Warning! D-Bus connection terminated.");

        bus_wait_for_units_clear(d);

        if (d->ready_callback)
                d->ready_callback(d, false, d->userdata);
        else /* If no ready callback is specified close the connection so that the event loop exits */
                sd_bus_close(sd_bus_message_get_bus(m));

        return 0;
}