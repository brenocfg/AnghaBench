#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* domains_next; scalar_t__ linked; } ;
struct TYPE_10__ {TYPE_3__* search_domain; int /*<<< orphan*/  scope; } ;
struct TYPE_9__ {struct TYPE_9__* domains_next; int /*<<< orphan*/  route_only; } ;
typedef  TYPE_1__ DnsSearchDomain ;
typedef  TYPE_2__ DnsQueryCandidate ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 TYPE_1__* dns_scope_get_search_domains (int /*<<< orphan*/ ) ; 
 TYPE_3__* dns_search_domain_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_search_domain_unref (TYPE_3__*) ; 

__attribute__((used)) static int dns_query_candidate_next_search_domain(DnsQueryCandidate *c) {
        DnsSearchDomain *next = NULL;

        assert(c);

        if (c->search_domain && c->search_domain->linked)
                next = c->search_domain->domains_next;
        else
                next = dns_scope_get_search_domains(c->scope);

        for (;;) {
                if (!next) /* We hit the end of the list */
                        return 0;

                if (!next->route_only)
                        break;

                /* Skip over route-only domains */
                next = next->domains_next;
        }

        dns_search_domain_unref(c->search_domain);
        c->search_domain = dns_search_domain_ref(next);

        return 1;
}