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
struct TYPE_4__ {void* output_io_event_source; void* input_io_event_source; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_OFF ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_set_enabled (void*,int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 

__attribute__((used)) static void bus_detach_io_events(sd_bus *bus) {
        assert(bus);

        if (bus->input_io_event_source) {
                sd_event_source_set_enabled(bus->input_io_event_source, SD_EVENT_OFF);
                bus->input_io_event_source = sd_event_source_unref(bus->input_io_event_source);
        }

        if (bus->output_io_event_source) {
                sd_event_source_set_enabled(bus->output_io_event_source, SD_EVENT_OFF);
                bus->output_io_event_source = sd_event_source_unref(bus->output_io_event_source);
        }
}