#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; TYPE_1__* network; int /*<<< orphan*/  ifname; } ;
struct TYPE_5__ {scalar_t__ ipv6_hop_limit; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  socket_ipv6_is_supported () ; 
 int sysctl_write_ip_property_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int link_set_ipv6_hop_limit(Link *link) {
        int r;

        /* Make this a NOP if IPv6 is not available */
        if (!socket_ipv6_is_supported())
                return 0;

        if (link->flags & IFF_LOOPBACK)
                return 0;

        if (!link->network)
                return 0;

        if (link->network->ipv6_hop_limit < 0)
                return 0;

        r = sysctl_write_ip_property_int(AF_INET6, link->ifname, "hop_limit", link->network->ipv6_hop_limit);
        if (r < 0)
                log_link_warning_errno(link, r, "Cannot set IPv6 hop limit for interface: %m");

        return 0;
}