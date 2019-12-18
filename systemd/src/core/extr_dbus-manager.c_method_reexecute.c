#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  objective; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_REEXECUTE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bus_verify_reload_daemon_async (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mac_selinux_access_check (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int verify_run_space (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_reexecute(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        int r;

        assert(message);
        assert(m);

        r = verify_run_space("Refusing to reexecute", error);
        if (r < 0)
                return r;

        r = mac_selinux_access_check(message, "reload", error);
        if (r < 0)
                return r;

        r = bus_verify_reload_daemon_async(m, message, error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* No authorization for now, but the async polkit stuff will call us again when it has it */

        /* We don't send a reply back here, the client should
         * just wait for us disconnecting. */

        m->objective = MANAGER_REEXECUTE;
        return 1;
}