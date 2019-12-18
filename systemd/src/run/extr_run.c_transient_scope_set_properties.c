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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_bus_message ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_SCOPE ; 
 int /*<<< orphan*/  arg_property ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_log_create_error (int) ; 
 scalar_t__ getpid_cached () ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,char*,char*,int,int /*<<< orphan*/ ) ; 
 int transient_cgroup_set_properties (int /*<<< orphan*/ *) ; 
 int transient_kill_set_properties (int /*<<< orphan*/ *) ; 
 int transient_unit_set_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transient_scope_set_properties(sd_bus_message *m) {
        int r;

        assert(m);

        r = transient_unit_set_properties(m, UNIT_SCOPE, arg_property);
        if (r < 0)
                return r;

        r = transient_kill_set_properties(m);
        if (r < 0)
                return r;

        r = transient_cgroup_set_properties(m);
        if (r < 0)
                return r;

        r = sd_bus_message_append(m, "(sv)", "PIDs", "au", 1, (uint32_t) getpid_cached());
        if (r < 0)
                return bus_log_create_error(r);

        return 0;
}