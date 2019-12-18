#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  slaves; int /*<<< orphan*/  manager; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifindex; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ link_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  link_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void link_drop_from_master(Link *link, NetDev *netdev) {
        Link *master;

        assert(link);

        if (!link->manager || !netdev)
                return;

        if (link_get(link->manager, netdev->ifindex, &master) < 0)
                return;

        link_unref(set_remove(master->slaves, link));
}