#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_5__ {char* id; TYPE_1__* manager; } ;
typedef  TYPE_2__ Unit ;
struct TYPE_4__ {int /*<<< orphan*/  polkit_registry; } ;

/* Variables and functions */
 char* GETTEXT_PACKAGE ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int bus_verify_polkit_async (int /*<<< orphan*/ *,int,char*,char const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bus_verify_manage_units_async_full(
                Unit *u,
                const char *verb,
                int capability,
                const char *polkit_message,
                bool interactive,
                sd_bus_message *call,
                sd_bus_error *error) {

        const char *details[9] = {
                "unit", u->id,
                "verb", verb,
        };

        if (polkit_message) {
                details[4] = "polkit.message";
                details[5] = polkit_message;
                details[6] = "polkit.gettext_domain";
                details[7] = GETTEXT_PACKAGE;
        }

        return bus_verify_polkit_async(
                        call,
                        capability,
                        "org.freedesktop.systemd1.manage-units",
                        details,
                        interactive,
                        UID_INVALID,
                        &u->manager->polkit_registry,
                        error);
}