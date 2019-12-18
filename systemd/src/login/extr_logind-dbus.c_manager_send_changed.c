#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_emit_properties_changed_strv (int /*<<< orphan*/ ,char*,char*,char**) ; 
 char** strv_from_stdarg_alloca (char const*) ; 

int manager_send_changed(Manager *manager, const char *property, ...) {
        char **l;

        assert(manager);

        l = strv_from_stdarg_alloca(property);

        return sd_bus_emit_properties_changed_strv(
                        manager->bus,
                        "/org/freedesktop/login1",
                        "org.freedesktop.login1.Manager",
                        l);
}