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
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_TIMER ; 
 int /*<<< orphan*/  arg_timer_property ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_log_create_error (int) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,int) ; 
 int transient_unit_set_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transient_timer_set_properties(sd_bus_message *m) {
        int r;

        assert(m);

        r = transient_unit_set_properties(m, UNIT_TIMER, arg_timer_property);
        if (r < 0)
                return r;

        /* Automatically clean up our transient timers */
        r = sd_bus_message_append(m, "(sv)", "RemainAfterElapse", "b", false);
        if (r < 0)
                return bus_log_create_error(r);

        return 0;
}