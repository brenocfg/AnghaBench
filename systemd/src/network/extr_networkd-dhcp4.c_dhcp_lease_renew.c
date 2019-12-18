#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sd_dhcp_lease ;
struct TYPE_10__ {int dhcp4_configured; int /*<<< orphan*/  dhcp_lease; int /*<<< orphan*/  keep_configuration; struct TYPE_10__* network; } ;
typedef  TYPE_1__ sd_dhcp_client ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_INFO_INFINITY_LIFE_TIME ; 
 int /*<<< orphan*/  FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEEP_CONFIGURATION_DHCP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dhcp4_update_address (TYPE_1__*,struct in_addr*,struct in_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_dirty (TYPE_1__*) ; 
 int log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int sd_dhcp_client_get_lease (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int sd_dhcp_lease_get_address (int /*<<< orphan*/ *,struct in_addr*) ; 
 int sd_dhcp_lease_get_lifetime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sd_dhcp_lease_get_netmask (int /*<<< orphan*/ *,struct in_addr*) ; 
 int /*<<< orphan*/  sd_dhcp_lease_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_dhcp_lease_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dhcp_lease_renew(sd_dhcp_client *client, Link *link) {
        sd_dhcp_lease *lease;
        struct in_addr address;
        struct in_addr netmask;
        uint32_t lifetime = CACHE_INFO_INFINITY_LIFE_TIME;
        int r;

        assert(link);
        assert(client);
        assert(link->network);

        r = sd_dhcp_client_get_lease(client, &lease);
        if (r < 0)
                return log_link_warning_errno(link, r, "DHCP error: no lease: %m");

        sd_dhcp_lease_unref(link->dhcp_lease);
        link->dhcp4_configured = false;
        link->dhcp_lease = sd_dhcp_lease_ref(lease);
        link_dirty(link);

        r = sd_dhcp_lease_get_address(lease, &address);
        if (r < 0)
                return log_link_warning_errno(link, r, "DHCP error: no address: %m");

        r = sd_dhcp_lease_get_netmask(lease, &netmask);
        if (r < 0)
                return log_link_warning_errno(link, r, "DHCP error: no netmask: %m");

        if (!FLAGS_SET(link->network->keep_configuration, KEEP_CONFIGURATION_DHCP)) {
                r = sd_dhcp_lease_get_lifetime(link->dhcp_lease, &lifetime);
                if (r < 0)
                        return log_link_warning_errno(link, r, "DHCP error: no lifetime: %m");
        }

        r = dhcp4_update_address(link, &address, &netmask, lifetime);
        if (r < 0)
                return log_link_warning_errno(link, r, "Could not update IP address: %m");

        return 0;
}