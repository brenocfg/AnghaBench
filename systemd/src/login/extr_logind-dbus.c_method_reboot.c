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
 int /*<<< orphan*/  INHIBIT_SHUTDOWN ; 
 int /*<<< orphan*/  SPECIAL_REBOOT_TARGET ; 
 int method_do_shutdown_or_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_reboot(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;

        return method_do_shutdown_or_sleep(
                        m, message,
                        SPECIAL_REBOOT_TARGET,
                        INHIBIT_SHUTDOWN,
                        "org.freedesktop.login1.reboot",
                        "org.freedesktop.login1.reboot-multiple-sessions",
                        "org.freedesktop.login1.reboot-ignore-inhibit",
                        NULL,
                        error);
}