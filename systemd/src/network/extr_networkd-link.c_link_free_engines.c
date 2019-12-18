#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  radv; int /*<<< orphan*/  ndisc; int /*<<< orphan*/  dhcp6_client; int /*<<< orphan*/  ipv4ll; int /*<<< orphan*/  lldp; int /*<<< orphan*/  dhcp_routes; int /*<<< orphan*/  dhcp_lease; int /*<<< orphan*/  dhcp_client; int /*<<< orphan*/  dhcp_server; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  ndisc_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_dhcp6_client_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dhcp_client_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dhcp_lease_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_dhcp_server_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ipv4ll_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_lldp_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ndisc_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_radv_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_free_engines(Link *link) {
        if (!link)
                return;

        link->dhcp_server = sd_dhcp_server_unref(link->dhcp_server);
        link->dhcp_client = sd_dhcp_client_unref(link->dhcp_client);
        link->dhcp_lease = sd_dhcp_lease_unref(link->dhcp_lease);
        link->dhcp_routes = set_free(link->dhcp_routes);

        link->lldp = sd_lldp_unref(link->lldp);

        ndisc_flush(link);

        link->ipv4ll = sd_ipv4ll_unref(link->ipv4ll);
        link->dhcp6_client = sd_dhcp6_client_unref(link->dhcp6_client);
        link->ndisc = sd_ndisc_unref(link->ndisc);
        link->radv = sd_radv_unref(link->radv);
}