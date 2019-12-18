#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct in_addr {int s_addr; } ;
typedef  int /*<<< orphan*/  sd_dhcp_lease ;
struct TYPE_9__ {struct in_addr in; } ;
struct TYPE_7__ {int s_addr; } ;
struct TYPE_8__ {TYPE_1__ in; } ;
struct TYPE_10__ {int /*<<< orphan*/  table; int /*<<< orphan*/  protocol; int /*<<< orphan*/  scope; TYPE_3__ prefsrc; int /*<<< orphan*/  dst_prefixlen; TYPE_2__ dst; int /*<<< orphan*/  family; } ;
typedef  TYPE_4__ Route ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  RTPROT_DHCP ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  in4_addr_netmask_to_prefixlen (struct in_addr*) ; 
 int route_new (TYPE_4__**) ; 
 int sd_dhcp_lease_get_netmask (int /*<<< orphan*/ *,struct in_addr*) ; 

__attribute__((used)) static int dhcp_prefix_route_from_lease(
                const sd_dhcp_lease *lease,
                uint32_t table,
                const struct in_addr *address,
                Route **ret_route) {

        Route *route;
        struct in_addr netmask;
        int r;

        r = sd_dhcp_lease_get_netmask((sd_dhcp_lease*) lease, &netmask);
        if (r < 0)
                return r;

        r = route_new(&route);
        if (r < 0)
                return r;

        route->family = AF_INET;
        route->dst.in.s_addr = address->s_addr & netmask.s_addr;
        route->dst_prefixlen = in4_addr_netmask_to_prefixlen(&netmask);
        route->prefsrc.in = *address;
        route->scope = RT_SCOPE_LINK;
        route->protocol = RTPROT_DHCP;
        route->table = table;
        *ret_route = route;
        return 0;
}