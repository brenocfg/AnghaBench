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
typedef  int /*<<< orphan*/  Unit ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  UNIT_PERSISTENT ; 
 int /*<<< orphan*/  UNIT_RUNTIME ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_unit_set_properties (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bus_verify_manage_units_async_full (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mac_selinux_unit_access_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,int*) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bus_unit_method_set_properties(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Unit *u = userdata;
        int runtime, r;

        assert(message);
        assert(u);

        r = mac_selinux_unit_access_check(u, message, "start", error);
        if (r < 0)
                return r;

        r = sd_bus_message_read(message, "b", &runtime);
        if (r < 0)
                return r;

        r = bus_verify_manage_units_async_full(
                        u,
                        "set-property",
                        CAP_SYS_ADMIN,
                        N_("Authentication is required to set properties on '$(unit)'."),
                        true,
                        message,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        r = bus_unit_set_properties(u, message, runtime ? UNIT_RUNTIME : UNIT_PERSISTENT, true, error);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}