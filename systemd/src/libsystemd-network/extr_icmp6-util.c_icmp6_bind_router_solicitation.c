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
struct ipv6_mreq {int ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; } ;
struct icmp6_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6_FILTER_SETBLOCKALL (struct icmp6_filter*) ; 
 int /*<<< orphan*/  ICMP6_FILTER_SETPASS (int /*<<< orphan*/ ,struct icmp6_filter*) ; 
 int /*<<< orphan*/  IN6ADDR_ALL_NODES_MULTICAST_INIT ; 
 int /*<<< orphan*/  ND_ROUTER_ADVERT ; 
 int icmp6_bind_router_message (struct icmp6_filter*,struct ipv6_mreq*) ; 

int icmp6_bind_router_solicitation(int index) {
        struct icmp6_filter filter = {};
        struct ipv6_mreq mreq = {
                .ipv6mr_multiaddr = IN6ADDR_ALL_NODES_MULTICAST_INIT,
                .ipv6mr_interface = index,
        };

        ICMP6_FILTER_SETBLOCKALL(&filter);
        ICMP6_FILTER_SETPASS(ND_ROUTER_ADVERT, &filter);

        return icmp6_bind_router_message(&filter, &mreq);
}