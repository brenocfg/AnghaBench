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
struct TYPE_9__ {TYPE_1__* network; } ;
struct TYPE_8__ {int /*<<< orphan*/  routes; } ;
typedef  TYPE_2__ Route ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  routes ; 

__attribute__((used)) static Route *route_free(Route *route) {
        if (!route)
                return NULL;

        if (route->network)
                LIST_REMOVE(routes, route->network->routes, route);

        return mfree(route);
}