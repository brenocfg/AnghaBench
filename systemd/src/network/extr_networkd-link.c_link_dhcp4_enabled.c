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
struct TYPE_6__ {int flags; scalar_t__ iftype; TYPE_1__* network; } ;
struct TYPE_5__ {int dhcp; scalar_t__ bond; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int ADDRESS_FAMILY_IPV4 ; 
 scalar_t__ ARPHRD_CAN ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

__attribute__((used)) static bool link_dhcp4_enabled(Link *link) {
        assert(link);

        if (link->flags & IFF_LOOPBACK)
                return false;

        if (!link->network)
                return false;

        if (link->network->bond)
                return false;

        if (link->iftype == ARPHRD_CAN)
                return false;

        return link->network->dhcp & ADDRESS_FAMILY_IPV4;
}