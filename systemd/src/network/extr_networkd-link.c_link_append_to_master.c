#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  slaves; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ NetDev ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int link_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  link_ref (TYPE_1__*) ; 
 int set_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int set_put (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int link_append_to_master(Link *link, NetDev *netdev) {
        Link *master;
        int r;

        assert(link);
        assert(netdev);

        r = link_get(link->manager, netdev->ifindex, &master);
        if (r < 0)
                return r;

        r = set_ensure_allocated(&master->slaves, NULL);
        if (r < 0)
                return r;

        r = set_put(master->slaves, link);
        if (r <= 0)
                return r;

        link_ref(link);
        return 0;
}