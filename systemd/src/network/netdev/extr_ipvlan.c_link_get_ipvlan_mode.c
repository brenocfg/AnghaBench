#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifname; int /*<<< orphan*/  manager; int /*<<< orphan*/  kind; } ;
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_2__ Link ;
typedef  int /*<<< orphan*/  IPVlanMode ;

/* Variables and functions */
 TYPE_5__* IPVLAN (TYPE_1__*) ; 
 scalar_t__ NETDEV_KIND_IPVLAN ; 
 int /*<<< orphan*/  _NETDEV_IPVLAN_MODE_INVALID ; 
 scalar_t__ netdev_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  streq_ptr (int /*<<< orphan*/ ,char*) ; 

IPVlanMode link_get_ipvlan_mode(Link *link) {
        NetDev *netdev;

        if (!streq_ptr(link->kind, "ipvlan"))
                return _NETDEV_IPVLAN_MODE_INVALID;

        if (netdev_get(link->manager, link->ifname, &netdev) < 0)
                return _NETDEV_IPVLAN_MODE_INVALID;

        if (netdev->kind != NETDEV_KIND_IPVLAN)
                return _NETDEV_IPVLAN_MODE_INVALID;

        return IPVLAN(netdev)->mode;
}