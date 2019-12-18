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
struct TYPE_5__ {scalar_t__ ifname; TYPE_1__* manager; } ;
struct TYPE_4__ {int /*<<< orphan*/  netdevs; } ;
typedef  TYPE_2__ NetDev ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void netdev_detach_from_manager(NetDev *netdev) {
        if (netdev->ifname && netdev->manager)
                hashmap_remove(netdev->manager->netdevs, netdev->ifname);
}