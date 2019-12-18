#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_dhcp_client ;
struct TYPE_5__ {void* dhcp_lease_old; void* dhcp_lease; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 void* TAKE_PTR (void*) ; 
 int dhcp_lease_acquired (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp_lease_lost (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_dhcp_lease_unref (void*) ; 

__attribute__((used)) static int dhcp_lease_ip_change(sd_dhcp_client *client, Link *link) {
        int r;

        link->dhcp_lease_old = TAKE_PTR(link->dhcp_lease);

        /* On ip address change, to keep the connectability, we would like to assign new address and
         * routes, and then release old lease. There are two possible success paths:
         *
         * 1. new address and routes are configured.
         *    -> handled by dhcp_release_old_lease() in dhcp4_route_handler().
         * 2. new address is configured and no route is requested.
         *    -> handled by dhcp_release_old_lease() in dhcp4_address_handler().
         *
         * On error in assigning new address and routes, then the link always enters to the failed
         * state. And link_enter_failed() leads to the DHCP client to be stopped. So,
         * dhcp_release_old_lease() will be also called by link_stop_clients().
         */

        r = dhcp_lease_acquired(client, link);
        if (r < 0) {
                /* If it fails, then the new address is not configured yet.
                 * So, let's simply drop the old lease. */
                sd_dhcp_lease_unref(link->dhcp_lease);
                link->dhcp_lease = TAKE_PTR(link->dhcp_lease_old);
                (void) dhcp_lease_lost(link);
                return r;
        }

        return 0;
}