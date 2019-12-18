#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ bond; } ;
struct TYPE_6__ {scalar_t__ iftype; TYPE_2__* network; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ link_ipv6ll_enabled (TYPE_1__*) ; 
 scalar_t__ network_has_static_ipv6_configurations (TYPE_2__*) ; 
 int /*<<< orphan*/  socket_ipv6_is_supported () ; 

__attribute__((used)) static bool link_ipv6_enabled(Link *link) {
        assert(link);

        if (!socket_ipv6_is_supported())
                return false;

        if (link->network->bond)
                return false;

        if (link->iftype == ARPHRD_CAN)
                return false;

        /* DHCPv6 client will not be started if no IPv6 link-local address is configured. */
        if (link_ipv6ll_enabled(link))
                return true;

        if (network_has_static_ipv6_configurations(link->network))
                return true;

        return false;
}