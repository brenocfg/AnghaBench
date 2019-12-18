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
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (TYPE_1__*) ; 
 int /*<<< orphan*/  MANAGER_REBOOT ; 
 int /*<<< orphan*/  SD_BUS_ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int mac_selinux_access_check (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int sd_bus_error_setf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_reply_method_return (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_reboot(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;
        int r;

        assert(message);
        assert(m);

        r = mac_selinux_access_check(message, "reboot", error);
        if (r < 0)
                return r;

        if (!MANAGER_IS_SYSTEM(m))
                return sd_bus_error_setf(error, SD_BUS_ERROR_NOT_SUPPORTED, "Reboot is only supported for system managers.");

        m->objective = MANAGER_REBOOT;

        return sd_bus_reply_method_return(message, NULL);
}