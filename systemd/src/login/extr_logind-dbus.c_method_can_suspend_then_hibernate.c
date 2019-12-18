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
 int /*<<< orphan*/  INHIBIT_SLEEP ; 
 int method_can_shutdown_or_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int method_can_suspend_then_hibernate(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        Manager *m = userdata;

        return method_can_shutdown_or_sleep(
                        m, message,
                        INHIBIT_SLEEP,
                        "org.freedesktop.login1.hibernate",
                        "org.freedesktop.login1.hibernate-multiple-sessions",
                        "org.freedesktop.login1.hibernate-ignore-inhibit",
                        "suspend-then-hibernate",
                        error);
}