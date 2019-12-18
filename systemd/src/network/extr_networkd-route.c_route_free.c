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
struct TYPE_10__ {int /*<<< orphan*/  expire; TYPE_1__* link; scalar_t__ section; TYPE_2__* network; } ;
struct TYPE_9__ {scalar_t__ n_static_routes; int /*<<< orphan*/  routes_by_section; int /*<<< orphan*/  static_routes; } ;
struct TYPE_8__ {int /*<<< orphan*/  routes_foreign; int /*<<< orphan*/  routes; } ;
typedef  TYPE_3__ Route ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  network_config_section_free (scalar_t__) ; 
 int /*<<< orphan*/  routes ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 

void route_free(Route *route) {
        if (!route)
                return;

        if (route->network) {
                LIST_REMOVE(routes, route->network->static_routes, route);

                assert(route->network->n_static_routes > 0);
                route->network->n_static_routes--;

                if (route->section)
                        hashmap_remove(route->network->routes_by_section, route->section);
        }

        network_config_section_free(route->section);

        if (route->link) {
                set_remove(route->link->routes, route);
                set_remove(route->link->routes_foreign, route);
        }

        sd_event_source_unref(route->expire);

        free(route);
}