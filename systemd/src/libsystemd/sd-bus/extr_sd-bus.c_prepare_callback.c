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
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_8__ {scalar_t__ output_fd; scalar_t__ input_fd; int /*<<< orphan*/  time_event_source; int /*<<< orphan*/  input_io_event_source; int /*<<< orphan*/  output_io_event_source; } ;
typedef  TYPE_1__ sd_event_source ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_enter_closing (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int sd_bus_get_events (TYPE_1__*) ; 
 int sd_bus_get_timeout (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int sd_event_source_set_enabled (int /*<<< orphan*/ ,int) ; 
 int sd_event_source_set_io_events (int /*<<< orphan*/ ,int) ; 
 int sd_event_source_set_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_callback(sd_event_source *s, void *userdata) {
        sd_bus *bus = userdata;
        int r, e;
        usec_t until;

        assert(s);
        assert(bus);

        e = sd_bus_get_events(bus);
        if (e < 0) {
                r = e;
                goto fail;
        }

        if (bus->output_fd != bus->input_fd) {

                r = sd_event_source_set_io_events(bus->input_io_event_source, e & POLLIN);
                if (r < 0)
                        goto fail;

                r = sd_event_source_set_io_events(bus->output_io_event_source, e & POLLOUT);
        } else
                r = sd_event_source_set_io_events(bus->input_io_event_source, e);
        if (r < 0)
                goto fail;

        r = sd_bus_get_timeout(bus, &until);
        if (r < 0)
                goto fail;
        if (r > 0) {
                int j;

                j = sd_event_source_set_time(bus->time_event_source, until);
                if (j < 0) {
                        r = j;
                        goto fail;
                }
        }

        r = sd_event_source_set_enabled(bus->time_event_source, r > 0);
        if (r < 0)
                goto fail;

        return 1;

fail:
        log_debug_errno(r, "Preparing of bus events failed, closing down: %m");
        bus_enter_closing(bus);

        return 1;
}