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
struct TYPE_10__ {TYPE_1__* manager; } ;
typedef  TYPE_2__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_2__ Transfer ;
struct TYPE_9__ {int /*<<< orphan*/  polkit_registry; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int bus_verify_polkit_async (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_reply_method_return (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int transfer_cancel (TYPE_2__*) ; 

__attribute__((used)) static int method_cancel(sd_bus_message *msg, void *userdata, sd_bus_error *error) {
        Transfer *t = userdata;
        int r;

        assert(msg);
        assert(t);

        r = bus_verify_polkit_async(
                        msg,
                        CAP_SYS_ADMIN,
                        "org.freedesktop.import1.pull",
                        NULL,
                        false,
                        UID_INVALID,
                        &t->manager->polkit_registry,
                        error);
        if (r < 0)
                return r;
        if (r == 0)
                return 1; /* Will call us back */

        r = transfer_cancel(t);
        if (r < 0)
                return r;

        return sd_bus_reply_method_return(msg, NULL);
}