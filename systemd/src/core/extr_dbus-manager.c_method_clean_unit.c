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
 int GENERIC_UNIT_LOAD ; 
 int GENERIC_UNIT_VALIDATE_LOADED ; 
 int /*<<< orphan*/  bus_unit_method_clean ; 
 int method_generic_unit_operation (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int method_clean_unit(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        /* Load the unit if necessary, in order to load it, and insist on the unit being loaded to be
         * cleaned */
        return method_generic_unit_operation(message, userdata, error, bus_unit_method_clean, GENERIC_UNIT_LOAD|GENERIC_UNIT_VALIDATE_LOADED);
}