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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ *,int,char*) ; 
 int sd_bus_message_append (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int unit_get_memory_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int property_get_current_memory(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        uint64_t sz = (uint64_t) -1;
        Unit *u = userdata;
        int r;

        assert(bus);
        assert(reply);
        assert(u);

        r = unit_get_memory_current(u, &sz);
        if (r < 0 && r != -ENODATA)
                log_unit_warning_errno(u, r, "Failed to get memory.usage_in_bytes attribute: %m");

        return sd_bus_message_append(reply, "t", sz);
}