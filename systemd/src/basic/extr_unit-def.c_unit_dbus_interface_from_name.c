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
typedef  scalar_t__ UnitType ;

/* Variables and functions */
 char const* unit_dbus_interface_from_type (scalar_t__) ; 
 scalar_t__ unit_name_to_type (char const*) ; 

const char *unit_dbus_interface_from_name(const char *name) {
        UnitType t;

        t = unit_name_to_type(name);
        if (t < 0)
                return NULL;

        return unit_dbus_interface_from_type(t);
}