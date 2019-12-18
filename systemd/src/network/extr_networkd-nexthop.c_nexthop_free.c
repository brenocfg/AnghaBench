#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* link; scalar_t__ section; TYPE_2__* network; } ;
struct TYPE_9__ {scalar_t__ n_static_nexthops; int /*<<< orphan*/  nexthops_by_section; int /*<<< orphan*/  static_nexthops; } ;
struct TYPE_8__ {int /*<<< orphan*/  nexthops_foreign; int /*<<< orphan*/  nexthops; } ;
typedef  TYPE_3__ NextHop ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  nexthops ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 

void nexthop_free(NextHop *nexthop) {
        if (!nexthop)
                return;

        if (nexthop->network) {
                LIST_REMOVE(nexthops, nexthop->network->static_nexthops, nexthop);

                assert(nexthop->network->n_static_nexthops > 0);
                nexthop->network->n_static_nexthops--;

                if (nexthop->section)
                        hashmap_remove(nexthop->network->nexthops_by_section, nexthop->section);
        }

        network_config_section_free(nexthop->section);

        if (nexthop->link) {
                set_remove(nexthop->link->nexthops, nexthop);
                set_remove(nexthop->link->nexthops_foreign, nexthop);
        }

        free(nexthop);
}