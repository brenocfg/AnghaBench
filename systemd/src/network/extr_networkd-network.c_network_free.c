#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dhcp_server_raw_options; int /*<<< orphan*/  dhcp_send_options; int /*<<< orphan*/  dnssec_negative_trust_anchors; int /*<<< orphan*/  dhcp_server_sip; int /*<<< orphan*/  dhcp_server_ntp; int /*<<< orphan*/  dhcp_server_dns; int /*<<< orphan*/  dhcp_server_timezone; int /*<<< orphan*/  name; int /*<<< orphan*/  duid; TYPE_1__* manager; int /*<<< orphan*/  qdiscs_by_section; int /*<<< orphan*/  rules_by_section; int /*<<< orphan*/  route_prefixes_by_section; int /*<<< orphan*/  prefixes_by_section; int /*<<< orphan*/  address_labels_by_section; int /*<<< orphan*/  neighbors_by_section; int /*<<< orphan*/  fdb_entries_by_section; int /*<<< orphan*/  nexthops_by_section; int /*<<< orphan*/  routes_by_section; int /*<<< orphan*/  addresses_by_section; int /*<<< orphan*/ * rules; int /*<<< orphan*/ * static_route_prefixes; int /*<<< orphan*/ * static_prefixes; int /*<<< orphan*/ * address_labels; int /*<<< orphan*/ * neighbors; int /*<<< orphan*/ * ipv6_proxy_ndp_addresses; int /*<<< orphan*/ * static_fdb_entries; int /*<<< orphan*/ * static_addresses; int /*<<< orphan*/ * static_nexthops; int /*<<< orphan*/ * static_routes; int /*<<< orphan*/  stacked_netdevs; int /*<<< orphan*/  vrf; int /*<<< orphan*/  bond; int /*<<< orphan*/  bridge; int /*<<< orphan*/  stacked_netdev_names; int /*<<< orphan*/  vrf_name; int /*<<< orphan*/  bond_name; int /*<<< orphan*/  bridge_name; int /*<<< orphan*/  ndisc_black_listed_prefix; int /*<<< orphan*/  router_dns; int /*<<< orphan*/  router_search_domains; int /*<<< orphan*/  bind_carrier; int /*<<< orphan*/  route_domains; int /*<<< orphan*/  search_domains; int /*<<< orphan*/  sip; int /*<<< orphan*/  dns; int /*<<< orphan*/  ntp; int /*<<< orphan*/  mac; int /*<<< orphan*/  dhcp_request_options; int /*<<< orphan*/  dhcp_black_listed_ip; int /*<<< orphan*/  dhcp_hostname; int /*<<< orphan*/  dhcp_user_class; int /*<<< orphan*/  dhcp_vendor_class_identifier; int /*<<< orphan*/  description; int /*<<< orphan*/  conditions; int /*<<< orphan*/  match_bssid; int /*<<< orphan*/  match_ssid; int /*<<< orphan*/  match_wlan_iftype; int /*<<< orphan*/  match_property; int /*<<< orphan*/  match_name; int /*<<< orphan*/  match_type; int /*<<< orphan*/  match_driver; int /*<<< orphan*/  match_path; int /*<<< orphan*/  match_mac; int /*<<< orphan*/  filename; } ;
struct TYPE_7__ {scalar_t__ duids_requesting_uuid; } ;
typedef  int /*<<< orphan*/  RoutingPolicyRule ;
typedef  int /*<<< orphan*/  RoutePrefix ;
typedef  int /*<<< orphan*/  Route ;
typedef  int /*<<< orphan*/  Prefix ;
typedef  int /*<<< orphan*/  NextHop ;
typedef  TYPE_2__ Network ;
typedef  int /*<<< orphan*/  Neighbor ;
typedef  int /*<<< orphan*/  IPv6ProxyNDPAddress ;
typedef  int /*<<< orphan*/  FdbEntry ;
typedef  int /*<<< orphan*/  AddressLabel ;
typedef  int /*<<< orphan*/  Address ;

/* Variables and functions */
 int /*<<< orphan*/  address_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  address_label_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  condition_free_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdb_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free_free_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  ipv6_proxy_ndp_address_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  neighbor_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nexthop_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ordered_hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ordered_set_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefix_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_free ; 
 int /*<<< orphan*/  route_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  route_prefix_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  routing_policy_rule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_remove (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Network *network_free(Network *network) {
        IPv6ProxyNDPAddress *ipv6_proxy_ndp_address;
        RoutePrefix *route_prefix;
        RoutingPolicyRule *rule;
        AddressLabel *label;
        FdbEntry *fdb_entry;
        Neighbor *neighbor;
        Address *address;
        NextHop *nexthop;
        Prefix *prefix;
        Route *route;

        if (!network)
                return NULL;

        free(network->filename);

        set_free_free(network->match_mac);
        strv_free(network->match_path);
        strv_free(network->match_driver);
        strv_free(network->match_type);
        strv_free(network->match_name);
        strv_free(network->match_property);
        strv_free(network->match_wlan_iftype);
        strv_free(network->match_ssid);
        set_free_free(network->match_bssid);
        condition_free_list(network->conditions);

        free(network->description);
        free(network->dhcp_vendor_class_identifier);
        strv_free(network->dhcp_user_class);
        free(network->dhcp_hostname);
        set_free(network->dhcp_black_listed_ip);
        set_free(network->dhcp_request_options);
        free(network->mac);

        strv_free(network->ntp);
        free(network->dns);
        strv_free(network->sip);
        ordered_set_free_free(network->search_domains);
        ordered_set_free_free(network->route_domains);
        strv_free(network->bind_carrier);

        ordered_set_free_free(network->router_search_domains);
        free(network->router_dns);
        set_free_free(network->ndisc_black_listed_prefix);

        free(network->bridge_name);
        free(network->bond_name);
        free(network->vrf_name);
        hashmap_free_free_key(network->stacked_netdev_names);
        netdev_unref(network->bridge);
        netdev_unref(network->bond);
        netdev_unref(network->vrf);
        hashmap_free_with_destructor(network->stacked_netdevs, netdev_unref);

        while ((route = network->static_routes))
                route_free(route);

        while ((nexthop = network->static_nexthops))
                nexthop_free(nexthop);

        while ((address = network->static_addresses))
                address_free(address);

        while ((fdb_entry = network->static_fdb_entries))
                fdb_entry_free(fdb_entry);

        while ((ipv6_proxy_ndp_address = network->ipv6_proxy_ndp_addresses))
                ipv6_proxy_ndp_address_free(ipv6_proxy_ndp_address);

        while ((neighbor = network->neighbors))
                neighbor_free(neighbor);

        while ((label = network->address_labels))
                address_label_free(label);

        while ((prefix = network->static_prefixes))
                prefix_free(prefix);

        while ((route_prefix = network->static_route_prefixes))
                route_prefix_free(route_prefix);

        while ((rule = network->rules))
                routing_policy_rule_free(rule);

        hashmap_free(network->addresses_by_section);
        hashmap_free(network->routes_by_section);
        hashmap_free(network->nexthops_by_section);
        hashmap_free(network->fdb_entries_by_section);
        hashmap_free(network->neighbors_by_section);
        hashmap_free(network->address_labels_by_section);
        hashmap_free(network->prefixes_by_section);
        hashmap_free(network->route_prefixes_by_section);
        hashmap_free(network->rules_by_section);
        ordered_hashmap_free_with_destructor(network->qdiscs_by_section, qdisc_free);

        if (network->manager &&
            network->manager->duids_requesting_uuid)
                set_remove(network->manager->duids_requesting_uuid, &network->duid);

        free(network->name);

        free(network->dhcp_server_timezone);
        free(network->dhcp_server_dns);
        free(network->dhcp_server_ntp);
        free(network->dhcp_server_sip);

        set_free_free(network->dnssec_negative_trust_anchors);

        ordered_hashmap_free(network->dhcp_send_options);
        ordered_hashmap_free(network->dhcp_server_raw_options);

        return mfree(network);
}