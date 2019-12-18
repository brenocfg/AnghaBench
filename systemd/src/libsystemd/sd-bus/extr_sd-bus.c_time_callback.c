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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_enter_closing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int sd_bus_process (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int time_callback(sd_event_source *s, uint64_t usec, void *userdata) {
        sd_bus *bus = userdata;
        int r;

        assert(bus);

        r = sd_bus_process(bus, NULL);
        if (r < 0) {
                log_debug_errno(r, "Processing of bus failed, closing down: %m");
                bus_enter_closing(bus);
        }

        return 1;
}