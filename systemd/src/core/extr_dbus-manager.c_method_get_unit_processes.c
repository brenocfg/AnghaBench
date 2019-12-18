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

/* Variables and functions */
 int /*<<< orphan*/  bus_unit_method_get_processes ; 
 int method_generic_unit_operation (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int method_get_unit_processes(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        /* Don't load a unit (since it won't have any processes if it's not loaded), but don't insist on the
         * unit being loaded (because even improperly loaded units might still have processes around */
        return method_generic_unit_operation(message, userdata, error, bus_unit_method_get_processes, 0);
}