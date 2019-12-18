#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct TYPE_19__ {int dhcp4_configured; struct TYPE_19__* dhcp_lease; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp_remove_address (TYPE_1__*,TYPE_1__*,struct in_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dhcp_remove_dns_routes (TYPE_1__*,TYPE_1__*,struct in_addr*,int) ; 
 int /*<<< orphan*/  dhcp_remove_router (TYPE_1__*,TYPE_1__*,struct in_addr*,int) ; 
 int /*<<< orphan*/  dhcp_remove_routes (TYPE_1__*,TYPE_1__*,struct in_addr*,int) ; 
 int /*<<< orphan*/  dhcp_reset_hostname (TYPE_1__*) ; 
 int /*<<< orphan*/  dhcp_reset_mtu (TYPE_1__*) ; 
 int /*<<< orphan*/  link_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  sd_dhcp_lease_get_address (TYPE_1__*,struct in_addr*) ; 
 TYPE_1__* sd_dhcp_lease_unref (TYPE_1__*) ; 

__attribute__((used)) static int dhcp_lease_lost(Link *link) {
        struct in_addr address = {};

        assert(link);
        assert(link->dhcp_lease);

        log_link_info(link, "DHCP lease lost");

        link->dhcp4_configured = false;

        (void) sd_dhcp_lease_get_address(link->dhcp_lease, &address);
        (void) dhcp_remove_routes(link, link->dhcp_lease, &address, true);
        (void) dhcp_remove_router(link, link->dhcp_lease, &address, true);
        (void) dhcp_remove_dns_routes(link, link->dhcp_lease, &address, true);
        (void) dhcp_remove_address(link, link->dhcp_lease, &address, NULL);
        (void) dhcp_reset_mtu(link);
        (void) dhcp_reset_hostname(link);

        link->dhcp_lease = sd_dhcp_lease_unref(link->dhcp_lease);
        link_dirty(link);

        return 0;
}