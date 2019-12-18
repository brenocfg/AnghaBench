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
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_4__ {scalar_t__ close_on_exit; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_close (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_bus_flush (TYPE_1__*) ; 

__attribute__((used)) static int quit_callback(sd_event_source *event, void *userdata) {
        sd_bus *bus = userdata;

        assert(event);

        if (bus->close_on_exit) {
                sd_bus_flush(bus);
                sd_bus_close(bus);
        }

        return 1;
}