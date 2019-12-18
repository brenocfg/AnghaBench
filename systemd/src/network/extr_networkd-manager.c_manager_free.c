#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct TYPE_15__ {scalar_t__ dhcp6_client; } ;
struct TYPE_14__ {struct TYPE_14__* dynamic_hostname; struct TYPE_14__* dynamic_timezone; int /*<<< orphan*/  bus; int /*<<< orphan*/  polkit_registry; int /*<<< orphan*/  device_monitor; int /*<<< orphan*/  event; int /*<<< orphan*/  speed_meter_event_source; int /*<<< orphan*/  resolve; int /*<<< orphan*/  genl; int /*<<< orphan*/  rtnl; void* rules_saved; void* rules_foreign; void* rules; int /*<<< orphan*/ * address_pools; void* netdevs; int /*<<< orphan*/  networks; int /*<<< orphan*/  duids_requesting_uuid; void* links; void* links_requesting_uuid; void* dirty_links; int /*<<< orphan*/  dhcp6_prefixes; struct TYPE_14__* state_file; } ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_2__ Link ;
typedef  int /*<<< orphan*/  AddressPool ;

/* Variables and functions */
 int /*<<< orphan*/  address_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_verify_polkit_async_registry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dhcp6_lease_pd_prefix_lost (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  dhcp6_prefix_remove (TYPE_1__*,struct in6_addr*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 struct in6_addr* hashmap_first_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 void* hashmap_free_with_destructor (void*,int /*<<< orphan*/  (*) (TYPE_2__*)) ; 
 TYPE_2__* hashmap_steal_first (void*) ; 
 int /*<<< orphan*/  link_stop_clients (TYPE_2__*,int) ; 
 int /*<<< orphan*/  link_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  netdev_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  network_unref ; 
 int /*<<< orphan*/  ordered_hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  routing_policy_rule_free (TYPE_2__*) ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_monitor_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_resolve_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 
 void* set_free_with_destructor (void*,int /*<<< orphan*/  (*) (TYPE_2__*)) ; 

void manager_free(Manager *m) {
        struct in6_addr *a;
        AddressPool *pool;
        Link *link;

        if (!m)
                return;

        free(m->state_file);

        while ((a = hashmap_first_key(m->dhcp6_prefixes)))
                (void) dhcp6_prefix_remove(m, a);
        m->dhcp6_prefixes = hashmap_free(m->dhcp6_prefixes);

        while ((link = hashmap_steal_first(m->links))) {
                if (link->dhcp6_client)
                        (void) dhcp6_lease_pd_prefix_lost(link->dhcp6_client, link);

                (void) link_stop_clients(link, true);

                link_unref(link);
        }

        m->dirty_links = set_free_with_destructor(m->dirty_links, link_unref);
        m->links_requesting_uuid = set_free_with_destructor(m->links_requesting_uuid, link_unref);
        m->links = hashmap_free_with_destructor(m->links, link_unref);

        m->duids_requesting_uuid = set_free(m->duids_requesting_uuid);
        m->networks = ordered_hashmap_free_with_destructor(m->networks, network_unref);

        m->netdevs = hashmap_free_with_destructor(m->netdevs, netdev_unref);

        while ((pool = m->address_pools))
                address_pool_free(pool);

        /* routing_policy_rule_free() access m->rules and m->rules_foreign.
         * So, it is necessary to set NULL after the sets are freed. */
        m->rules = set_free_with_destructor(m->rules, routing_policy_rule_free);
        m->rules_foreign = set_free_with_destructor(m->rules_foreign, routing_policy_rule_free);
        set_free_with_destructor(m->rules_saved, routing_policy_rule_free);

        sd_netlink_unref(m->rtnl);
        sd_netlink_unref(m->genl);
        sd_resolve_unref(m->resolve);

        sd_event_source_unref(m->speed_meter_event_source);
        sd_event_unref(m->event);

        sd_device_monitor_unref(m->device_monitor);

        bus_verify_polkit_async_registry_free(m->polkit_registry);
        sd_bus_flush_close_unref(m->bus);

        free(m->dynamic_timezone);
        free(m->dynamic_hostname);

        free(m);
}