#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * routes; int /*<<< orphan*/ * addresses; int /*<<< orphan*/  bond; int /*<<< orphan*/  bridge; int /*<<< orphan*/  vlan; int /*<<< orphan*/  dns; int /*<<< orphan*/  hostname; int /*<<< orphan*/  ifname; } ;
typedef  int /*<<< orphan*/  Route ;
typedef  TYPE_1__ Network ;
typedef  int /*<<< orphan*/  Address ;

/* Variables and functions */
 int /*<<< orphan*/  address_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  route_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Network *network_free(Network *network) {
        Address *address;
        Route *route;

        if (!network)
                return NULL;

        free(network->ifname);
        free(network->hostname);
        strv_free(network->dns);
        free(network->vlan);
        free(network->bridge);
        free(network->bond);

        while ((address = network->addresses))
                address_free(address);

        while ((route = network->routes))
                route_free(route);

        return mfree(network);
}