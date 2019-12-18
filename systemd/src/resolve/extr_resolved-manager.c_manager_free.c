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
struct TYPE_11__ {int /*<<< orphan*/  trust_anchor; int /*<<< orphan*/  dnssd_services; int /*<<< orphan*/  mdns_hostname; int /*<<< orphan*/  llmnr_hostname; int /*<<< orphan*/  full_hostname; int /*<<< orphan*/  hostname_fd; int /*<<< orphan*/  hostname_event_source; int /*<<< orphan*/  mdns_host_ipv6_key; int /*<<< orphan*/  mdns_host_ipv4_key; int /*<<< orphan*/  llmnr_host_ipv6_key; int /*<<< orphan*/  llmnr_host_ipv4_key; int /*<<< orphan*/  event; int /*<<< orphan*/  sigrtmin1_event_source; int /*<<< orphan*/  sigusr2_event_source; int /*<<< orphan*/  sigusr1_event_source; int /*<<< orphan*/  bus; int /*<<< orphan*/  polkit_registry; int /*<<< orphan*/  rtnl_event_source; int /*<<< orphan*/  rtnl; int /*<<< orphan*/  network_monitor; int /*<<< orphan*/  network_event_source; int /*<<< orphan*/  dns_transactions; int /*<<< orphan*/  links; scalar_t__ dns_streams; int /*<<< orphan*/  unicast_scope; scalar_t__ dns_queries; int /*<<< orphan*/  search_domains; int /*<<< orphan*/  fallback_dns_servers; int /*<<< orphan*/  dns_servers; } ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  Link ;
typedef  int /*<<< orphan*/  DnssdService ;

/* Variables and functions */
 int /*<<< orphan*/  bus_verify_polkit_async_registry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_query_free (scalar_t__) ; 
 int /*<<< orphan*/  dns_resource_key_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_scope_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_search_domain_unlink_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_server_unlink_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_stream_unref (scalar_t__) ; 
 int /*<<< orphan*/  dns_trust_anchor_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnssd_service_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnstls_manager_free (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 void* hashmap_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_dns_stub_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_etc_hosts_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_llmnr_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_mdns_stop (TYPE_1__*) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_network_monitor_unref (int /*<<< orphan*/ ) ; 

Manager *manager_free(Manager *m) {
        Link *l;
        DnssdService *s;

        if (!m)
                return NULL;

        dns_server_unlink_all(m->dns_servers);
        dns_server_unlink_all(m->fallback_dns_servers);
        dns_search_domain_unlink_all(m->search_domains);

        while ((l = hashmap_first(m->links)))
               link_free(l);

        while (m->dns_queries)
                dns_query_free(m->dns_queries);

        dns_scope_free(m->unicast_scope);

        /* At this point only orphaned streams should remain. All others should have been freed already by their
         * owners */
        while (m->dns_streams)
                dns_stream_unref(m->dns_streams);

#if ENABLE_DNS_OVER_TLS
        dnstls_manager_free(m);
#endif

        hashmap_free(m->links);
        hashmap_free(m->dns_transactions);

        sd_event_source_unref(m->network_event_source);
        sd_network_monitor_unref(m->network_monitor);

        sd_netlink_unref(m->rtnl);
        sd_event_source_unref(m->rtnl_event_source);

        manager_llmnr_stop(m);
        manager_mdns_stop(m);
        manager_dns_stub_stop(m);

        bus_verify_polkit_async_registry_free(m->polkit_registry);

        sd_bus_flush_close_unref(m->bus);

        sd_event_source_unref(m->sigusr1_event_source);
        sd_event_source_unref(m->sigusr2_event_source);
        sd_event_source_unref(m->sigrtmin1_event_source);

        sd_event_unref(m->event);

        dns_resource_key_unref(m->llmnr_host_ipv4_key);
        dns_resource_key_unref(m->llmnr_host_ipv6_key);
        dns_resource_key_unref(m->mdns_host_ipv4_key);
        dns_resource_key_unref(m->mdns_host_ipv6_key);

        sd_event_source_unref(m->hostname_event_source);
        safe_close(m->hostname_fd);

        free(m->full_hostname);
        free(m->llmnr_hostname);
        free(m->mdns_hostname);

        while ((s = hashmap_first(m->dnssd_services)))
               dnssd_service_free(s);
        hashmap_free(m->dnssd_services);

        dns_trust_anchor_flush(&m->trust_anchor);
        manager_etc_hosts_flush(m);

        return mfree(m);
}