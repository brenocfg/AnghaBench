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
 int method_create_machine_internal (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_create_machine_with_network(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        return method_create_machine_internal(message, true, userdata, error);
}