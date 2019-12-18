#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  network; void* slaves; int /*<<< orphan*/  bound_by_links; int /*<<< orphan*/  bound_to_links; int /*<<< orphan*/  sd_device; int /*<<< orphan*/  state_file; int /*<<< orphan*/  ssid; int /*<<< orphan*/  kind; int /*<<< orphan*/  ifname; int /*<<< orphan*/  lldp_file; int /*<<< orphan*/  lease_file; int /*<<< orphan*/ * pool_addresses; void* addresses_foreign; void* addresses; void* neighbors_foreign; void* neighbors; void* nexthops_foreign; void* nexthops; void* routes_foreign; void* routes; } ;
typedef  TYPE_1__ Link ;
typedef  int /*<<< orphan*/  Address ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  address_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addresses ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_dns_settings_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  link_free_engines (TYPE_1__*) ; 
 int /*<<< orphan*/  link_lldp_emit_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  link_ntp_settings_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  link_unref (int /*<<< orphan*/ *) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  neighbor_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nexthop_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  route_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_device_unref (int /*<<< orphan*/ ) ; 
 void* set_free_with_destructor (void*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Link *link_free(Link *link) {
        Address *address;

        assert(link);

        link_ntp_settings_clear(link);
        link_dns_settings_clear(link);

        link->routes = set_free_with_destructor(link->routes, route_free);
        link->routes_foreign = set_free_with_destructor(link->routes_foreign, route_free);

        link->nexthops = set_free_with_destructor(link->nexthops, nexthop_free);
        link->nexthops_foreign = set_free_with_destructor(link->nexthops_foreign, nexthop_free);

        link->neighbors = set_free_with_destructor(link->neighbors, neighbor_free);
        link->neighbors_foreign = set_free_with_destructor(link->neighbors_foreign, neighbor_free);

        link->addresses = set_free_with_destructor(link->addresses, address_free);
        link->addresses_foreign = set_free_with_destructor(link->addresses_foreign, address_free);

        while ((address = link->pool_addresses)) {
                LIST_REMOVE(addresses, link->pool_addresses, address);
                address_free(address);
        }

        link_lldp_emit_stop(link);
        link_free_engines(link);
        free(link->lease_file);
        free(link->lldp_file);

        free(link->ifname);
        free(link->kind);
        free(link->ssid);

        (void) unlink(link->state_file);
        free(link->state_file);

        sd_device_unref(link->sd_device);

        hashmap_free(link->bound_to_links);
        hashmap_free(link->bound_by_links);

        set_free_with_destructor(link->slaves, link_unref);

        network_unref(link->network);

        return mfree(link);
}