#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ master_ifindex; TYPE_1__* network; } ;
struct TYPE_4__ {scalar_t__ bridge; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int IFF_SLAVE ; 

__attribute__((used)) static bool link_is_enslaved(Link *link) {
        if (link->flags & IFF_SLAVE)
                /* Even if the link is not managed by networkd, honor IFF_SLAVE flag. */
                return true;

        if (!link->network)
                return false;

        if (link->master_ifindex > 0 && link->network->bridge)
                return true;

        /* TODO: add conditions for other netdevs. */

        return false;
}