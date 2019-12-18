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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_2__ {int /*<<< orphan*/  (* bus_name_owner_change ) (int /*<<< orphan*/ *,char const*,char const*) ;} ;

/* Variables and functions */
 TYPE_1__* UNIT_VTABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_log_parse_error (int) ; 
 char* empty_to_null (char const*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char const**,char const**,char const**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static int signal_name_owner_changed(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        const char *name, *old_owner, *new_owner;
        Unit *u = userdata;
        int r;

        assert(message);
        assert(u);

        r = sd_bus_message_read(message, "sss", &name, &old_owner, &new_owner);
        if (r < 0) {
                bus_log_parse_error(r);
                return 0;
        }

        old_owner = empty_to_null(old_owner);
        new_owner = empty_to_null(new_owner);

        if (UNIT_VTABLE(u)->bus_name_owner_change)
                UNIT_VTABLE(u)->bus_name_owner_change(u, old_owner, new_owner);

        return 0;
}