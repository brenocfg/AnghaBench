#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_3__ {int /*<<< orphan*/  id; int /*<<< orphan*/  manager; } ;
typedef  int /*<<< orphan*/  Scope ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ERROR_SCOPE_NOT_RUNNING ; 
 int ESTALE ; 
 TYPE_1__* UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_verify_manage_units_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mac_selinux_unit_access_check (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int scope_abandon (int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bus_scope_method_abandon(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Scope *s = userdata;
        int r;

        assert(message);
        assert(s);

        r = mac_selinux_unit_access_check(UNIT(s), message, "stop", error);
        if (r < 0)
                return r;

        r = bus_verify_manage_units_async(UNIT(s)->manager, message, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        r = scope_abandon(s);
        if (r == -ESTALE)
                return sd_bus_error_setf(error, BUS_ERROR_SCOPE_NOT_RUNNING, "Scope %s is not running, cannot abandon.", UNIT(s)->id);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}