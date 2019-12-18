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
struct TYPE_9__ {scalar_t__ n_neighbors; int /*<<< orphan*/  neighbors_by_section; int /*<<< orphan*/  neighbors; } ;
struct TYPE_8__ {int /*<<< orphan*/  neighbors_foreign; int /*<<< orphan*/  neighbors; } ;
typedef  TYPE_3__ Neighbor ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  neighbors ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 

void neighbor_free(Neighbor *neighbor) {
        if (!neighbor)
                return;

        if (neighbor->network) {
                LIST_REMOVE(neighbors, neighbor->network->neighbors, neighbor);
                assert(neighbor->network->n_neighbors > 0);
                neighbor->network->n_neighbors--;

                if (neighbor->section)
                        hashmap_remove(neighbor->network->neighbors_by_section, neighbor->section);
        }

        network_config_section_free(neighbor->section);

        if (neighbor->link) {
                set_remove(neighbor->link->neighbors, neighbor);
                set_remove(neighbor->link->neighbors_foreign, neighbor);
        }

        free(neighbor);
}