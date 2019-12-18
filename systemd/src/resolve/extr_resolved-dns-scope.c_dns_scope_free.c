#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ family; TYPE_2__* manager; int /*<<< orphan*/  zone; int /*<<< orphan*/  cache; int /*<<< orphan*/  announce_event_source; int /*<<< orphan*/  conflict_event_source; int /*<<< orphan*/  conflict_queue; int /*<<< orphan*/  transactions_by_key; scalar_t__ query_candidates; int /*<<< orphan*/  protocol; TYPE_1__* link; } ;
struct TYPE_13__ {int /*<<< orphan*/  dns_scopes; } ;
struct TYPE_12__ {char* ifname; } ;
typedef  TYPE_3__ DnsScope ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* af_to_name (scalar_t__) ; 
 int /*<<< orphan*/  dns_cache_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_protocol_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_query_candidate_free (scalar_t__) ; 
 int /*<<< orphan*/  dns_resource_record_unref ; 
 int /*<<< orphan*/  dns_scope_abort_transactions (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_scope_llmnr_membership (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dns_scope_mdns_membership (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dns_zone_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* mfree (TYPE_3__*) ; 
 int /*<<< orphan*/  ordered_hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scopes ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

DnsScope* dns_scope_free(DnsScope *s) {
        if (!s)
                return NULL;

        log_debug("Removing scope on link %s, protocol %s, family %s", s->link ? s->link->ifname : "*", dns_protocol_to_string(s->protocol), s->family == AF_UNSPEC ? "*" : af_to_name(s->family));

        dns_scope_llmnr_membership(s, false);
        dns_scope_mdns_membership(s, false);
        dns_scope_abort_transactions(s);

        while (s->query_candidates)
                dns_query_candidate_free(s->query_candidates);

        hashmap_free(s->transactions_by_key);

        ordered_hashmap_free_with_destructor(s->conflict_queue, dns_resource_record_unref);
        sd_event_source_unref(s->conflict_event_source);

        sd_event_source_unref(s->announce_event_source);

        dns_cache_flush(&s->cache);
        dns_zone_flush(&s->zone);

        LIST_REMOVE(scopes, s->manager->dns_scopes, s);
        return mfree(s);
}