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
typedef  int /*<<< orphan*/  uint32_t ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sd_dhcp6_lease ;
typedef  int /*<<< orphan*/  sd_dhcp6_client ;
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int dhcp6_address_change (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_dhcp6_client_get_lease (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_dhcp6_lease_get_address (int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_dhcp6_lease_reset_address_iter (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dhcp6_lease_address_acquired(sd_dhcp6_client *client, Link *link) {
        int r;
        sd_dhcp6_lease *lease;
        struct in6_addr ip6_addr;
        uint32_t lifetime_preferred, lifetime_valid;

        r = sd_dhcp6_client_get_lease(client, &lease);
        if (r < 0)
                return r;

        sd_dhcp6_lease_reset_address_iter(lease);

        while (sd_dhcp6_lease_get_address(lease, &ip6_addr,
                                                 &lifetime_preferred,
                                                 &lifetime_valid) >= 0) {

                r = dhcp6_address_change(link, &ip6_addr, lifetime_preferred, lifetime_valid);
                if (r < 0)
                        return r;
        }

        return 0;
}