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
struct TYPE_10__ {struct TYPE_10__* dhcp_client; struct TYPE_10__* ipv4ll; struct TYPE_10__* event; struct TYPE_10__* manager; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_FAMILY_IPV4 ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ link_dhcp4_enabled (TYPE_1__*) ; 
 scalar_t__ link_ipv4ll_enabled (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_1__*,char*) ; 
 int log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int sd_dhcp_client_start (TYPE_1__*) ; 
 int sd_ipv4ll_start (TYPE_1__*) ; 

__attribute__((used)) static int link_acquire_ipv4_conf(Link *link) {
        int r;

        assert(link);
        assert(link->manager);
        assert(link->manager->event);

        if (link_ipv4ll_enabled(link, ADDRESS_FAMILY_IPV4)) {
                assert(link->ipv4ll);

                log_link_debug(link, "Acquiring IPv4 link-local address");

                r = sd_ipv4ll_start(link->ipv4ll);
                if (r < 0)
                        return log_link_warning_errno(link, r, "Could not acquire IPv4 link-local address: %m");
        }

        if (link_dhcp4_enabled(link)) {
                assert(link->dhcp_client);

                log_link_debug(link, "Acquiring DHCPv4 lease");

                r = sd_dhcp_client_start(link->dhcp_client);
                if (r < 0)
                        return log_link_warning_errno(link, r, "Could not acquire DHCPv4 lease: %m");
        }

        return 0;
}