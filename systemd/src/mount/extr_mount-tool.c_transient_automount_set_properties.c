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
 int /*<<< orphan*/  UNIT_AUTOMOUNT ; 
 scalar_t__ USEC_INFINITY ; 
 int /*<<< orphan*/  arg_automount_property ; 
 scalar_t__ arg_timeout_idle ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,scalar_t__) ; 
 int transient_unit_set_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transient_automount_set_properties(sd_bus_message *m) {
        int r;

        assert(m);

        r = transient_unit_set_properties(m, UNIT_AUTOMOUNT, arg_automount_property);
        if (r < 0)
                return r;

        if (arg_timeout_idle != USEC_INFINITY) {
                r = sd_bus_message_append(m, "(sv)", "TimeoutIdleUSec", "t", arg_timeout_idle);
                if (r < 0)
                        return r;
        }

        return 0;
}