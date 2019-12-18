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
typedef  int /*<<< orphan*/  sd_bus ;
typedef  int CGroupMask ;
typedef  scalar_t__ CGroupController ;

/* Variables and functions */
 int CGROUP_CONTROLLER_TO_MASK (scalar_t__) ; 
 scalar_t__ _CGROUP_CONTROLLER_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_controller_to_string (scalar_t__) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sd_bus_message_close_container (int /*<<< orphan*/ *) ; 
 int sd_bus_message_open_container (int /*<<< orphan*/ *,char,char*) ; 

__attribute__((used)) static int property_get_cgroup_mask(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        CGroupMask *mask = userdata;
        CGroupController ctrl;
        int r;

        assert(bus);
        assert(reply);

        r = sd_bus_message_open_container(reply, 'a', "s");
        if (r < 0)
                return r;

        for (ctrl = 0; ctrl < _CGROUP_CONTROLLER_MAX; ctrl++) {
                if ((*mask & CGROUP_CONTROLLER_TO_MASK(ctrl)) == 0)
                        continue;

                r = sd_bus_message_append(reply, "s", cgroup_controller_to_string(ctrl));
                if (r < 0)
                        return r;
        }

        return sd_bus_message_close_container(reply);
}