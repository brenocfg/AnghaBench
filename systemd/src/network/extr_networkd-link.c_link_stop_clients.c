#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ radv; scalar_t__ ndisc; scalar_t__ dhcp6_client; scalar_t__ ipv4ll; scalar_t__ dhcp_client; TYPE_1__* network; scalar_t__ restarting; struct TYPE_9__* manager; struct TYPE_9__* event; } ;
struct TYPE_8__ {int /*<<< orphan*/  keep_configuration; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEEP_CONFIGURATION_DHCP_ON_STOP ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dhcp4_release_old_lease (TYPE_2__*) ; 
 int /*<<< orphan*/  link_lldp_emit_stop (TYPE_2__*) ; 
 int log_link_warning_errno (TYPE_2__*,int,char*) ; 
 int sd_dhcp6_client_stop (scalar_t__) ; 
 int sd_dhcp_client_stop (scalar_t__) ; 
 int sd_ipv4ll_stop (scalar_t__) ; 
 int sd_ndisc_stop (scalar_t__) ; 
 int sd_radv_stop (scalar_t__) ; 

int link_stop_clients(Link *link, bool may_keep_dhcp) {
        int r = 0, k;

        assert(link);
        assert(link->manager);
        assert(link->manager->event);

        dhcp4_release_old_lease(link);

        bool keep_dhcp = may_keep_dhcp &&
                         link->network &&
                         (link->manager->restarting ||
                          FLAGS_SET(link->network->keep_configuration, KEEP_CONFIGURATION_DHCP_ON_STOP));

        if (link->dhcp_client && !keep_dhcp) {
                k = sd_dhcp_client_stop(link->dhcp_client);
                if (k < 0)
                        r = log_link_warning_errno(link, k, "Could not stop DHCPv4 client: %m");
        }

        if (link->ipv4ll) {
                k = sd_ipv4ll_stop(link->ipv4ll);
                if (k < 0)
                        r = log_link_warning_errno(link, k, "Could not stop IPv4 link-local: %m");
        }

        if (link->dhcp6_client) {
                k = sd_dhcp6_client_stop(link->dhcp6_client);
                if (k < 0)
                        r = log_link_warning_errno(link, k, "Could not stop DHCPv6 client: %m");
        }

        if (link->ndisc) {
                k = sd_ndisc_stop(link->ndisc);
                if (k < 0)
                        r = log_link_warning_errno(link, k, "Could not stop IPv6 Router Discovery: %m");
        }

        if (link->radv) {
                k = sd_radv_stop(link->radv);
                if (k < 0)
                        r = log_link_warning_errno(link, k, "Could not stop IPv6 Router Advertisement: %m");
        }

        link_lldp_emit_stop(link);
        return r;
}