#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* manager; int /*<<< orphan*/  uid; } ;
typedef  TYPE_2__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_2__ User ;
struct TYPE_9__ {int /*<<< orphan*/  polkit_registry; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_KILL ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int bus_verify_polkit_async (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int user_stop (TYPE_2__*,int) ; 

int bus_user_method_terminate(sd_bus_message *message, void *userdata, sd_bus_error *error) {
        User *u = userdata;
        int r;

        assert(message);
        assert(u);

        r = bus_verify_polkit_async(
                        message,
                        CAP_KILL,
                        "org.freedesktop.login1.manage",
                        NULL,
                        false,
                        u->uid,
                        &u->manager->polkit_registry,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Will call us back */

        r = user_stop(u, true);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(message, NULL);
}