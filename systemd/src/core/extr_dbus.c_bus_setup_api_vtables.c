#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus ;
typedef  size_t UnitType ;
struct TYPE_2__ {scalar_t__ cgroup_context_offset; scalar_t__ exec_context_offset; scalar_t__ kill_context_offset; int /*<<< orphan*/  bus_vtable; } ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 size_t _UNIT_TYPE_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 int /*<<< orphan*/  bus_cgroup_context_find ; 
 int /*<<< orphan*/  bus_cgroup_vtable ; 
 int /*<<< orphan*/  bus_exec_context_find ; 
 int /*<<< orphan*/  bus_exec_vtable ; 
 int /*<<< orphan*/  bus_job_enumerate ; 
 int /*<<< orphan*/  bus_job_find ; 
 int /*<<< orphan*/  bus_job_vtable ; 
 int /*<<< orphan*/  bus_kill_context_find ; 
 int /*<<< orphan*/  bus_kill_vtable ; 
 int /*<<< orphan*/  bus_manager_vtable ; 
 int /*<<< orphan*/  bus_unit_cgroup_find ; 
 int /*<<< orphan*/  bus_unit_cgroup_vtable ; 
 int /*<<< orphan*/  bus_unit_enumerate ; 
 int /*<<< orphan*/  bus_unit_find ; 
 int /*<<< orphan*/  bus_unit_interface_find ; 
 int /*<<< orphan*/  bus_unit_vtable ; 
 int log_error_errno (int,char*,...) ; 
 int /*<<< orphan*/  mac_selinux_filter ; 
 int sd_bus_add_fallback_vtable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_bus_add_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_bus_add_node_enumerator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_bus_add_object_vtable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* unit_dbus_interface_from_type (size_t) ; 
 TYPE_1__** unit_vtable ; 

__attribute__((used)) static int bus_setup_api_vtables(Manager *m, sd_bus *bus) {
        UnitType t;
        int r;

        assert(m);
        assert(bus);

#if HAVE_SELINUX
        r = sd_bus_add_filter(bus, NULL, mac_selinux_filter, m);
        if (r < 0)
                return log_error_errno(r, "Failed to add SELinux access filter: %m");
#endif

        r = sd_bus_add_object_vtable(bus, NULL, "/org/freedesktop/systemd1", "org.freedesktop.systemd1.Manager", bus_manager_vtable, m);
        if (r < 0)
                return log_error_errno(r, "Failed to register Manager vtable: %m");

        r = sd_bus_add_fallback_vtable(bus, NULL, "/org/freedesktop/systemd1/job", "org.freedesktop.systemd1.Job", bus_job_vtable, bus_job_find, m);
        if (r < 0)
                return log_error_errno(r, "Failed to register Job vtable: %m");

        r = sd_bus_add_node_enumerator(bus, NULL, "/org/freedesktop/systemd1/job", bus_job_enumerate, m);
        if (r < 0)
                return log_error_errno(r, "Failed to add job enumerator: %m");

        r = sd_bus_add_fallback_vtable(bus, NULL, "/org/freedesktop/systemd1/unit", "org.freedesktop.systemd1.Unit", bus_unit_vtable, bus_unit_find, m);
        if (r < 0)
                return log_error_errno(r, "Failed to register Unit vtable: %m");

        r = sd_bus_add_node_enumerator(bus, NULL, "/org/freedesktop/systemd1/unit", bus_unit_enumerate, m);
        if (r < 0)
                return log_error_errno(r, "Failed to add job enumerator: %m");

        for (t = 0; t < _UNIT_TYPE_MAX; t++) {
                const char *interface;

                assert_se(interface = unit_dbus_interface_from_type(t));

                r = sd_bus_add_fallback_vtable(bus, NULL, "/org/freedesktop/systemd1/unit", interface, unit_vtable[t]->bus_vtable, bus_unit_interface_find, m);
                if (r < 0)
                        return log_error_errno(r, "Failed to register type specific vtable for %s: %m", interface);

                if (unit_vtable[t]->cgroup_context_offset > 0) {
                        r = sd_bus_add_fallback_vtable(bus, NULL, "/org/freedesktop/systemd1/unit", interface, bus_unit_cgroup_vtable, bus_unit_cgroup_find, m);
                        if (r < 0)
                                return log_error_errno(r, "Failed to register control group unit vtable for %s: %m", interface);

                        r = sd_bus_add_fallback_vtable(bus, NULL, "/org/freedesktop/systemd1/unit", interface, bus_cgroup_vtable, bus_cgroup_context_find, m);
                        if (r < 0)
                                return log_error_errno(r, "Failed to register control group vtable for %s: %m", interface);
                }

                if (unit_vtable[t]->exec_context_offset > 0) {
                        r = sd_bus_add_fallback_vtable(bus, NULL, "/org/freedesktop/systemd1/unit", interface, bus_exec_vtable, bus_exec_context_find, m);
                        if (r < 0)
                                return log_error_errno(r, "Failed to register execute vtable for %s: %m", interface);
                }

                if (unit_vtable[t]->kill_context_offset > 0) {
                        r = sd_bus_add_fallback_vtable(bus, NULL, "/org/freedesktop/systemd1/unit", interface, bus_kill_vtable, bus_kill_context_find, m);
                        if (r < 0)
                                return log_error_errno(r, "Failed to register kill vtable for %s: %m", interface);
                }
        }

        return 0;
}