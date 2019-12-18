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
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int bus_verify_manage_units_async (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mac_selinux_access_check (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_reset_failed (int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_reset_failed(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        int r;

        assert(message);
        assert(m);

        r = mac_selinux_access_check(message, "reload", error);
        if (r < 0)
                return r;

        r = bus_verify_manage_units_async(m, message, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        manager_reset_failed(m);

        return sd_bus_reply_method_return(message, NULL);
}