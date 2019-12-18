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
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_NO_SUCH_UNIT ; 
 int /*<<< orphan*/ * manager_get_unit_by_cgroup (int /*<<< orphan*/ *,char const*) ; 
 int reply_unit_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**) ; 

__attribute__((used)) static int method_get_unit_by_control_group(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        const char *cgroup;
        Unit *u;
        int r;

        r = sd_bus_message_read(message, "s", &cgroup);
        if (r < 0)
                return r;

        u = manager_get_unit_by_cgroup(m, cgroup);
        if (!u)
                return sd_bus_error_setf(error, BUS_ERROR_NO_SUCH_UNIT, "Control group '%s' is not valid or not managed by this instance", cgroup);

        return reply_unit_path(u, message, error);
}