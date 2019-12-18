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
struct TYPE_6__ {int flags; TYPE_1__* network; } ;
struct TYPE_5__ {scalar_t__ ipv6_proxy_ndp; scalar_t__ n_ipv6_proxy_ndp_addresses; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

__attribute__((used)) static bool ipv6_proxy_ndp_is_needed(Link *link) {
        assert(link);

        if (link->flags & IFF_LOOPBACK)
                return false;

        if (!link->network)
                return false;

        if (link->network->ipv6_proxy_ndp >= 0)
                return link->network->ipv6_proxy_ndp;

        if (link->network->n_ipv6_proxy_ndp_addresses == 0)
                return false;

        return true;
}