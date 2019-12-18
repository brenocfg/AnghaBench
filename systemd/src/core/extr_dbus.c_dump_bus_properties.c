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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_automount_vtable ; 
 int /*<<< orphan*/  bus_cgroup_vtable ; 
 int /*<<< orphan*/  bus_device_vtable ; 
 int /*<<< orphan*/  bus_exec_vtable ; 
 int /*<<< orphan*/  bus_job_vtable ; 
 int /*<<< orphan*/  bus_kill_vtable ; 
 int /*<<< orphan*/  bus_manager_vtable ; 
 int /*<<< orphan*/  bus_mount_vtable ; 
 int /*<<< orphan*/  bus_path_vtable ; 
 int /*<<< orphan*/  bus_scope_vtable ; 
 int /*<<< orphan*/  bus_service_vtable ; 
 int /*<<< orphan*/  bus_slice_vtable ; 
 int /*<<< orphan*/  bus_socket_vtable ; 
 int /*<<< orphan*/  bus_swap_vtable ; 
 int /*<<< orphan*/  bus_target_vtable ; 
 int /*<<< orphan*/  bus_timer_vtable ; 
 int /*<<< orphan*/  bus_unit_cgroup_vtable ; 
 int /*<<< orphan*/  bus_unit_vtable ; 
 int /*<<< orphan*/  vtable_dump_bus_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dump_bus_properties(FILE *f) {
        assert(f);

        vtable_dump_bus_properties(f, bus_automount_vtable);
        vtable_dump_bus_properties(f, bus_cgroup_vtable);
        vtable_dump_bus_properties(f, bus_device_vtable);
        vtable_dump_bus_properties(f, bus_exec_vtable);
        vtable_dump_bus_properties(f, bus_job_vtable);
        vtable_dump_bus_properties(f, bus_kill_vtable);
        vtable_dump_bus_properties(f, bus_manager_vtable);
        vtable_dump_bus_properties(f, bus_mount_vtable);
        vtable_dump_bus_properties(f, bus_path_vtable);
        vtable_dump_bus_properties(f, bus_scope_vtable);
        vtable_dump_bus_properties(f, bus_service_vtable);
        vtable_dump_bus_properties(f, bus_slice_vtable);
        vtable_dump_bus_properties(f, bus_socket_vtable);
        vtable_dump_bus_properties(f, bus_swap_vtable);
        vtable_dump_bus_properties(f, bus_target_vtable);
        vtable_dump_bus_properties(f, bus_timer_vtable);
        vtable_dump_bus_properties(f, bus_unit_vtable);
        vtable_dump_bus_properties(f, bus_unit_cgroup_vtable);
}