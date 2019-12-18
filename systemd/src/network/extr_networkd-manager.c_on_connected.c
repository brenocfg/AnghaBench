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
struct TYPE_8__ {scalar_t__ links_requesting_uuid; scalar_t__ dynamic_timezone; scalar_t__ dynamic_hostname; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_request_product_uuid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_set_hostname (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  manager_set_timezone (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int on_connected(sd_bus_message *message, void *userdata, sd_bus_error *ret_error) {
        Manager *m = userdata;

        assert(message);
        assert(m);

        /* Did we get a timezone or transient hostname from DHCP while D-Bus wasn't up yet? */
        if (m->dynamic_hostname)
                (void) manager_set_hostname(m, m->dynamic_hostname);
        if (m->dynamic_timezone)
                (void) manager_set_timezone(m, m->dynamic_timezone);
        if (m->links_requesting_uuid)
                (void) manager_request_product_uuid(m, NULL);

        return 0;
}