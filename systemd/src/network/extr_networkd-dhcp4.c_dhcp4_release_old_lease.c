#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct TYPE_16__ {struct TYPE_16__* dhcp_lease_old; struct TYPE_16__* dhcp_lease; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp_remove_address (TYPE_1__*,TYPE_1__*,struct in_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dhcp_remove_dns_routes (TYPE_1__*,TYPE_1__*,struct in_addr*,int) ; 
 int /*<<< orphan*/  dhcp_remove_router (TYPE_1__*,TYPE_1__*,struct in_addr*,int) ; 
 int /*<<< orphan*/  dhcp_remove_routes (TYPE_1__*,TYPE_1__*,struct in_addr*,int) ; 
 int /*<<< orphan*/  in4_addr_equal (struct in_addr*,struct in_addr*) ; 
 int /*<<< orphan*/  link_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_dhcp_lease_get_address (TYPE_1__*,struct in_addr*) ; 
 TYPE_1__* sd_dhcp_lease_unref (TYPE_1__*) ; 

void dhcp4_release_old_lease(Link *link) {
        struct in_addr address = {}, address_old = {};

        assert(link);

        if (!link->dhcp_lease_old)
                return;

        assert(link->dhcp_lease);

        (void) sd_dhcp_lease_get_address(link->dhcp_lease_old, &address_old);
        (void) sd_dhcp_lease_get_address(link->dhcp_lease, &address);

        (void) dhcp_remove_routes(link, link->dhcp_lease_old, &address_old, false);
        (void) dhcp_remove_router(link, link->dhcp_lease_old, &address_old, false);
        (void) dhcp_remove_dns_routes(link, link->dhcp_lease_old, &address_old, false);

        if (!in4_addr_equal(&address_old, &address))
                (void) dhcp_remove_address(link, link->dhcp_lease_old, &address_old, NULL);

        link->dhcp_lease_old = sd_dhcp_lease_unref(link->dhcp_lease_old);
        link_dirty(link);
}