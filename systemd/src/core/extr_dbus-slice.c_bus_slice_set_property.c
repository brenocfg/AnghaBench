#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  UnitWriteFlags ;
typedef  char const Unit ;
struct TYPE_3__ {int /*<<< orphan*/  cgroup_context; } ;
typedef  TYPE_1__ Slice ;

/* Variables and functions */
 TYPE_1__* SLICE (char const*) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int bus_cgroup_set_property (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bus_slice_set_property(
                Unit *u,
                const char *name,
                sd_bus_message *message,
                UnitWriteFlags flags,
                sd_bus_error *error) {

        Slice *s = SLICE(u);

        assert(name);
        assert(u);

        return bus_cgroup_set_property(u, &s->cgroup_context, name, message, flags, error);
}