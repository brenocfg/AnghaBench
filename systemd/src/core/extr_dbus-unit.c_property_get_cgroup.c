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
struct TYPE_8__ {scalar_t__ cgroup_path; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* empty_to_root (scalar_t__) ; 
 int sd_bus_message_append (TYPE_1__*,char*,char const*) ; 

__attribute__((used)) static int property_get_cgroup(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Unit *u = userdata;
        const char *t = NULL;

        assert(bus);
        assert(reply);
        assert(u);

        /* Three cases: a) u->cgroup_path is NULL, in which case the
         * unit has no control group, which we report as the empty
         * string. b) u->cgroup_path is the empty string, which
         * indicates the root cgroup, which we report as "/". c) all
         * other cases we report as-is. */

        if (u->cgroup_path)
                t = empty_to_root(u->cgroup_path);

        return sd_bus_message_append(reply, "s", t);
}