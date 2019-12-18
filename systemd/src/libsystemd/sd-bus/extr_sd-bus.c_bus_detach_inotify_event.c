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
struct TYPE_4__ {scalar_t__ inotify_event_source; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_OFF ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_source_unref (scalar_t__) ; 

__attribute__((used)) static void bus_detach_inotify_event(sd_bus *bus) {
        assert(bus);

        if (bus->inotify_event_source) {
                sd_event_source_set_enabled(bus->inotify_event_source, SD_EVENT_OFF);
                bus->inotify_event_source = sd_event_source_unref(bus->inotify_event_source);
        }
}